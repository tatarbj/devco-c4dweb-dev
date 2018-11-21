<?php

use PhpOffice\PhpSpreadsheet\Spreadsheet;
use PhpOffice\PhpSpreadsheet\Writer\Xlsx;
use PhpOffice\PhpSpreadsheet\Helper\Html;
use PhpOffice\PhpSpreadsheet\Shared\StringHelper;
use PhpOffice\PhpSpreadsheet\RichText\RichText;

/**
 * @file
 * Provides the object to export indicators as an Excel file.
 */

/**
 * Class to export indicators as an Excel file based on the given diagram.
 */
class C4dRcdExcelExportIndicators {

  /**
   * The full array for current diagram.
   *
   * @var array
   *
   * @see _c4d_rcd_load_full_diagram()
   */
  public $diagram;

  /**
   * The spreadsheet object.
   *
   * @var PhpOffice\PhpSpreadsheet\Spreadsheet
   */
  protected $spreadsheet;

  /**
   * The active sheet object.
   *
   * @var PhpOffice\PhpSpreadsheet\Worksheet
   */
  protected $activeSheet;

  /**
   * The HTML helper object.
   *
   * @var PhpOffice\PhpSpreadsheet\Helper\Html
   */
  protected $html;

  /**
   * The current row for the active sheet.
   *
   * @var int
   *    Active spreadsheet row index.
   */
  protected $current_row;

  /**
   * The time at which the class has been instanciated.
   *
   * @var int
   *    UNIX timestamp.
   */
  protected $request_time;

  /**
   * Constructor.
   */
  public function __construct($diagram) {
    // Initialize values.
    $this->diagram = $diagram;
    $this->spreadsheet = new Spreadsheet();
    $this->activeSheet = $this->spreadsheet->getActiveSheet();
    $this->html = new Html();
    $this->current_row = 1;
    $this->request_time = time();
    $this->init();
  }

  /**
   * Sets the initial settings for the spreadsheet.
   */
  protected function init() {
    $columns = ['A', 'B', 'C', 'D', 'E', 'F'];
    foreach ($columns as $column) {
      // This is for XLSX.
      $this->activeSheet->getColumnDimension($column)->setWidth(42.6);
      // This is for XLS.
//      $this->activeSheet->getColumnDimension($column)->setWidth(298);
    }

    // Set metadata for the file.
    $date = date(DATE_RFC2822, $this->request_time);
    $this->spreadsheet->getProperties()->setCreator('capacity4dev')
      ->setTitle($this->diagram['diagram']->title)
      ->setSubject(t("Indicators for @title", ['@title' => $this->diagram['diagram']->title]))
      ->setDescription(t("This document has been generated from https://europa.eu/capacity4dev/ on @date", ['@date' => $date]));
    // setTitle() throws an exception if title is longer than 31 characters
    // long, so wee need to cut it beforehand.
    // @see https://github.com/PHPOffice/PhpSpreadsheet/issues/176
    $title = truncate_utf8($this->diagram['diagram']->title, \PhpOffice\PhpSpreadsheet\Worksheet\Worksheet::SHEET_TITLE_MAXIMUM_LENGTH, FALSE, TRUE);
    $this->activeSheet->setTitle($title);
  }

  /**
   * Adds the impacts/results/indicators to the spreadsheet.
   */
  protected function setImpacts() {
    if (empty($this->diagram['impacts'])) {
      return;
    }

    // Set the section title. In this case 'Impact'.
    $this->activeSheet->getStyle("A$this->current_row:F$this->current_row")->applyFromArray($this->getSectionStyling());
    $this->activeSheet->mergeCells("A$this->current_row:F$this->current_row")->setCellValue("A$this->current_row", strtoupper(t('Impact')));
    $this->current_row++;

    foreach ($this->diagram['impacts'] as $impact) {
      $impact_wrapper = entity_metadata_wrapper(C4D_RCD_ENTITY_TYPE, $impact);

      // Cycle through indicators to find the related items.
      $nb_indicators = 0;
      foreach ($this->diagram['indicators'] as $indicator) {
        $indicator_wrapper = entity_metadata_wrapper(C4D_RCD_ENTITY_TYPE, $indicator);

        if ($indicator_wrapper->field_rcd_result->raw() != $impact->id) {
          continue;
        }

        if ($nb_indicators == 0) {
          $this->setIndicatorsHeaders();
        }

        $field_rcd_unit = !empty($indicator->field_rcd_unit) ? $indicator_wrapper->field_rcd_unit->value() : NULL;
        $field_rcd_additional_information = !empty($indicator->field_rcd_additional_information) ? $indicator_wrapper->field_rcd_additional_information->value->value() : NULL;
        $field_rcd_data_source = !empty($indicator->field_rcd_data_source) ? $indicator_wrapper->field_rcd_data_source->value->value() : NULL;
        $field_rcd_type_of_data_source = !empty($indicator->field_rcd_type_of_data_source) ? $indicator_wrapper->field_rcd_type_of_data_source->value() : NULL;

        $this->activeSheet->setCellValue("B$this->current_row", $this->sanitizePlainTextContent($indicator_wrapper->title->value()) . "\n");
        $this->activeSheet->setCellValue("C$this->current_row", $this->formatHTMLContent($field_rcd_unit) . "\n");
        $this->activeSheet->setCellValue("D$this->current_row", $this->formatHTMLContent($field_rcd_additional_information) . "\n");
        $this->activeSheet->setCellValue("E$this->current_row", $this->formatHTMLContent($field_rcd_data_source) . "\n");
        $this->activeSheet->setCellValue("F$this->current_row", $this->formatHTMLContent($field_rcd_type_of_data_source) . "\n");
        $nb_indicators++;
        $this->current_row++;
      }

      // Set the impact's title for all indicators.
      switch ($nb_indicators) {
        case 0:
          $starting_row = $this->current_row;
          $ending_row = $this->current_row;
          $this->current_row++;
          break;

        case 1:
          $starting_row = $this->current_row - 1;
          $ending_row = $this->current_row - 1;
          break;

        default:
          $starting_row = $this->current_row - $nb_indicators;
          $ending_row = $this->current_row - 1;
          break;
      }

      $richtext = new RichText();
      $richtext->createText(t('Impact:') . "\n\n");      
      $title = $richtext->createTextRun($this->sanitizePlainTextContent($impact_wrapper->field_rcd_svg_element->descr->value()));
      $title->getFont()->setBold(TRUE);
      $this->activeSheet->mergeCells("A$starting_row:A$ending_row")->setCellValue("A$starting_row", $richtext);
    }
  }

  /**
   * Adds the priority areas/results/indicators to the spreadsheet.
   */
  protected function setPriorityAreas() {
    if (empty($this->diagram['priority_areas'])) {
      return;
    }

    foreach ($this->diagram['priority_areas'] as $priority_area) {
      $priority_wrapper = entity_metadata_wrapper(C4D_RCD_ENTITY_TYPE, $priority_area);

      // Set the priority area title as section title.
      $title = $this->sanitizePlainTextContent($priority_wrapper->title->value());
      $this->activeSheet->getStyle("A$this->current_row:F$this->current_row")->applyFromArray($this->getSectionStyling());
      $this->activeSheet->mergeCells("A$this->current_row:F$this->current_row")->setCellValue("A$this->current_row", strtoupper($title));
      $this->current_row++;


      // Cycle through results to find the related items.
      foreach ($this->diagram['results'] as $result) {
        $result_wrapper = entity_metadata_wrapper(C4D_RCD_ENTITY_TYPE, $result);

        if ($result_wrapper->field_rcd_priority_area->raw() != $priority_area->id) {
          continue;
        }

        // Cycle through indicators to find the related items.
        $nb_indicators = 0;
        foreach ($this->diagram['indicators'] as $indicator) {
          $indicator_wrapper = entity_metadata_wrapper(C4D_RCD_ENTITY_TYPE, $indicator);

          if ($indicator_wrapper->field_rcd_result->raw() != $result->id) {
            continue;
          }

          if ($nb_indicators == 0) {
            $this->setIndicatorsHeaders();
          }

          $field_rcd_unit = !empty($indicator->field_rcd_unit) ? $indicator_wrapper->field_rcd_unit->value() : NULL;
          $field_rcd_additional_information = !empty($indicator->field_rcd_additional_information) ? $indicator_wrapper->field_rcd_additional_information->value->value() : NULL;
          $field_rcd_data_source = !empty($indicator->field_rcd_data_source) ? $indicator_wrapper->field_rcd_data_source->value->value() : NULL;
          $field_rcd_type_of_data_source = !empty($indicator->field_rcd_type_of_data_source) ? $indicator_wrapper->field_rcd_type_of_data_source->value() : NULL;

          $this->activeSheet->setCellValue("B$this->current_row", $this->sanitizePlainTextContent($indicator_wrapper->title->value()) . "\n");
          $this->activeSheet->setCellValue("C$this->current_row", $this->formatHTMLContent($field_rcd_unit) . "\n");
          $this->activeSheet->setCellValue("D$this->current_row", $this->formatHTMLContent($field_rcd_additional_information) . "\n");
          $this->activeSheet->setCellValue("E$this->current_row", $this->formatHTMLContent($field_rcd_data_source) . "\n");
          $this->activeSheet->setCellValue("F$this->current_row", $this->formatHTMLContent($field_rcd_type_of_data_source) . "\n");
          $nb_indicators++;
          $this->current_row++;
        }

        // Set the result title for all indicators.
        switch ($nb_indicators) {
          case 0:
            $starting_row = $this->current_row;
            $ending_row = $this->current_row;
            $this->current_row++;
            break;

          case 1:
            $starting_row = $this->current_row - 1;
            $ending_row = $this->current_row - 1;
            break;

          default:
            $starting_row = $this->current_row - $nb_indicators;
            $ending_row = $this->current_row - 1;
            break;
        }

        $richtext = new RichText();
        $allowed_types = $result_wrapper->field_rcd_type->optionsList();
        $heading = '';
        if (isset($allowed_types[$result_wrapper->field_rcd_type->value()])) {
          $heading = $allowed_types[$result_wrapper->field_rcd_type->value()] . ':' . "\n\n";
        }
        $richtext->createText($heading);
        $title = $richtext->createTextRun($this->sanitizePlainTextContent($result_wrapper->field_rcd_svg_element->descr->value()));
        $title->getFont()->setBold(TRUE);
        $this->activeSheet->mergeCells("A$starting_row:A$ending_row")->setCellValue("A$starting_row", $richtext);
      }
    }
  }

  /**
   * Sets the indicators headers in the active sheet.
   */
  protected function setIndicatorsHeaders() {
    // Set the column header titles.
    $this->activeSheet->setCellValue("A$this->current_row", t('Result'));
    $this->activeSheet->setCellValue("B$this->current_row", t('Indicator(s)'));
    $this->activeSheet->setCellValue("C$this->current_row", t('Unit'));
    $this->activeSheet->setCellValue("D$this->current_row", t('Additional Information'));
    $this->activeSheet->setCellValue("E$this->current_row", t('Data Source(s)'));
    $this->activeSheet->setCellValue("F$this->current_row", t('Type of data Source'));

    // Set styling for these cells.
    $this->activeSheet->getStyle("A$this->current_row:F$this->current_row")
      ->getFill()->setFillType(\PhpOffice\PhpSpreadsheet\Style\Fill::FILL_SOLID)->getStartColor()->setRGB('CCCCCC');

    $this->current_row++;
  }

  /**
   * Returns an array to be used by
   * PhpOffice\PhpSpreadsheet\Style\Style->applyFromArray().
   *
   * @return array
   *    Array containing style values.
   */
  protected function getSectionStyling() {
    $styles = [
      'font' => [
        'bold' => TRUE,
        'size' => 16,
      ],
      'alignment' => [
        'horizontal' => PhpOffice\PhpSpreadsheet\Style\Alignment::HORIZONTAL_CENTER,
      ],
      'fill' => [
        'fillType' => \PhpOffice\PhpSpreadsheet\Style\Fill::FILL_SOLID,
        'startColor' => [
            'rgb' => '9FC2E1',
        ],
      ],
      'borders' => [
          'top' => [
              'borderStyle' => \PhpOffice\PhpSpreadsheet\Style\Border::BORDER_DOTTED,
          ],
      ],
    ];

    return $styles;
  }

  /**
   * Apply formatting globally to all cells.
   */
  protected function formatAllCells() {
    // Set general styling.
    $styleArray = [
      'borders' => [
        'allBorders' => [
          'borderStyle' => \PhpOffice\PhpSpreadsheet\Style\Border::BORDER_THIN,
        ],
      ],
      'alignment' => [
        'wrapText' => TRUE,
        'vertical' => PhpOffice\PhpSpreadsheet\Style\Alignment::VERTICAL_CENTER,
      ],
    ];
    $this->activeSheet->getStyle('A1:F' . ($this->current_row - 1))->applyFromArray($styleArray);

    // Select the next row to avoid having all the sheet selected.
    $this->activeSheet->setSelectedCells("A$this->current_row");
  }

  /**
   * Prepares an HTML string to be added into a cell.
   *
   * @param string $html
   *    The HTML content to be prepared.
   *
   * @return RichText
   *    The rich text object.
   */
  protected function formatHTMLContent($html) {
    //$html = StringHelper::sanitizeUTF8($html);
    return $this->html->toRichTextObject($html);
  }

  /**
   * Sanitizes a string to be used in a cell as plain text.
   *
   * @param string $string
   *    The text to sanitize.
   *
   * @return string
   *    The sanitized string.
   */
  protected function sanitizePlainTextContent($string) {
    // Remove new lines.
    $string = str_replace(["\n", "\r"], ' ', $string);

    // Remove multiple consecutive spaces.
    $string = preg_replace('/\s+/', ' ', $string);

    return $string;
  }

  /**
   * Performs all needed actions to build the spreadsheet and outputs it to the
   * requesting browser as file download.
   */
  public function export() {
    // Perform needed actions to fill in the form with data and formatting.
    $this->setImpacts();
    $this->setPriorityAreas();
    $this->formatAllCells();
 
    // Define the filename.
    // We assume that transliteration is always enabled, if it's not we may be
    // in trouble and this code needs to be improved.
    $title = $this->diagram['diagram']->title;
    if (module_exists('transliteration')) {
      $title = transliteration_clean_filename($this->diagram['diagram']->title);
    }
    $filename = $title . '-' . date('Ymd-\THisO');

    // XLSX format.
    $writer = new Xlsx($this->spreadsheet);
    $writer->setOffice2003Compatibility(TRUE);
    header('Content-Type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet');
    header('Content-Disposition: attachment;filename="' . $filename . '.xlsx"');
    header("Cache-Control: no-store, no-cache, must-revalidate, max-age=0");
    header("Cache-Control: post-check=0, pre-check=0", FALSE);
    header("Pragma: no-cache");

    // XLS format.
//    $writer = new Xls($this->spreadsheet);
//    $filename = 'test';
//    header('Content-Type: application/vnd.ms-excel');
//    header('Content-Disposition: attachment;filename="' . $filename . '.xls"');
//    header("Cache-Control: no-store, no-cache, must-revalidate, max-age=0");
//    header("Cache-Control: post-check=0, pre-check=0", FALSE);
//    header("Pragma: no-cache");

    return $writer->save('php://output');
  }

}
