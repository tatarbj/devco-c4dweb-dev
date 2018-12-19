<?php

/**
 * This class is the migration class for Results.
 */
class C4DRcdResultMigration extends C4DRcdBaseMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Results');

    $query = Database::getConnection()->select('legacy_elementi', 'e')
      ->condition('vertical', 0)
      ->condition('colonna', [12, 13], 'NOT IN')
      ->fields('e', []);

    $this->source = new MigrateSourceSQL($query, [], NULL, ['cache_counts' => TRUE]);

    // Set up our destination.
    $this->destination = new MigrateDestinationEntityAPI(C4DRcdBaseMigration::DEST_ENTITY_TYPE, C4DRcdBaseMigration::DEST_BUNDLE_RESULT);

    $this->map = new MigrateSQLMap($this->machineName,
      [
        'id' => [
          'type' => 'int',
          'not null' => TRUE,
          'description' => 'Result ID.',
          'alias' => 'e',
        ],
      ],
      MigrateDestinationEntityAPI::getKeySchema(C4DRcdBaseMigration::DEST_ENTITY_TYPE)
    );

    // Mapped fields
    $this->addFieldMapping('title', 'titolo')
      ->description(t('Mapping priority area description in source to entity title'));
    $this->addFieldMapping('field_rcd_svg_element', 'vertical');
    $this->addFieldMapping('field_rcd_svg_element:vertical', 'vertical');
    $this->addFieldMapping('field_rcd_svg_element:tipo', 'tipo');
    $this->addFieldMapping('field_rcd_svg_element:colonna', 'colonna')->sourceMigration('C4DRcdPriorityArea');
    $this->addFieldMapping('field_rcd_svg_element:x', 'x');
    $this->addFieldMapping('field_rcd_svg_element:y', 'y');
    $this->addFieldMapping('field_rcd_svg_element:width', 'width');
    $this->addFieldMapping('field_rcd_svg_element:height', 'height');
    $this->addFieldMapping('field_rcd_svg_element:riga_1', 'riga_1');
    $this->addFieldMapping('field_rcd_svg_element:riga_2', 'riga_2');
    $this->addFieldMapping('field_rcd_svg_element:riga_3', 'riga_3');
    $this->addFieldMapping('field_rcd_svg_element:z_index', 'z_index');
    $this->addFieldMapping('field_rcd_svg_element:contatore_z', 'contatore_z');
    $this->addFieldMapping('field_rcd_svg_element:titolo', 'titolo');
    $this->addFieldMapping('field_rcd_svg_element:descr', 'descr');
    $this->addFieldMapping('field_rcd_svg_element:hovering', 'hovering');
    $this->addFieldMapping('field_rcd_svg_element:http_type', 'http_type');
    $this->addFieldMapping('field_rcd_svg_element:color', 'bg_color');
    $this->addFieldMapping('field_rcd_svg_element:ordine', 'ordine');
//      ->description(t('Mapping elementi in source to field_rcd_svg_element'));
    $this->addFieldMapping('field_rcd_priority_area', 'colonna')->sourceMigration('C4DRcdPriorityArea')
      ->description(t('Mapping colonna in source to field_rcd_priority_area'));
    $this->addFieldMapping('field_rcd_diagram', 'id_prj')->sourceMigration('C4DRcdDiagram')
      ->description(t('Mapping id_prj in source to field_rcd_diagram'));
    $this->addFieldMapping('field_rcd_type', 'result_type')
      ->description(t('Mapping priority area description in source to entity title'));
  }

  public function prepare($entity, $row) {
    // For some obscure reason, fields that have 0 as value are considered as
    // null, so we need to set them ourselves directly in the entity.
    $affected_fields = [
      'vertical',
      'tipo',
      'ordine',
      'contatore_z',
    ];
    foreach ($affected_fields as $field_name) {
      if (isset($row->{$field_name}) && $row->{$field_name} == '0') {
        $entity->field_rcd_svg_element[LANGUAGE_NONE][0][$field_name] = (string) $row->{$field_name};
      }
    }
  }

  public function prepareRow($row) {
    $row->vertical = (int) $row->vertical;
    $row->tipo = (int) $row->tipo;
    $row->ordine = (int) $row->ordine;
    $row->contatore_z = (int) $row->contatore_z;
    switch ($row->tipo) {
      case 1:
        $row->result_type = 'output';
        break;

      case 2:
        $row->result_type = 'outcome';
        break;
    }
  }
}