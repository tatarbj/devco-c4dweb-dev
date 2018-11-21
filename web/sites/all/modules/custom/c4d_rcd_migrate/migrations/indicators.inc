<?php

/**
 * This class is the migration class for Indicators.
 */
class C4DRcdIndicatorMigration extends C4DRcdBaseMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Indicators');

    $query = Database::getConnection('default', 'legacy')->select('web_indicators', 'i')
      ->fields('i', []);

    $this->source = new MigrateSourceSQL($query, [], NULL, ['cache_counts' => TRUE]);

    // Set up our destination.
    $this->destination = new MigrateDestinationEntityAPI(C4DRcdBaseMigration::DEST_ENTITY_TYPE, C4DRcdBaseMigration::DEST_BUNDLE_INDICATOR);

    $this->map = new MigrateSQLMap($this->machineName,
      [
        'id' => [
          'type' => 'int',
          'not null' => TRUE,
          'description' => 'Indicator ID.',
          'alias' => 'i',
        ],
      ],
      MigrateDestinationEntityAPI::getKeySchema(C4DRcdBaseMigration::DEST_ENTITY_TYPE)
    );

    // Mapped fields
    $this->addFieldMapping('title', 'titolo')
      ->description(t('Mapping priority area description in source to entity title'));
    $this->addFieldMapping('field_rcd_result', 'id_result')->sourceMigration(['C4DRcdResult', 'C4DRcdImpact']);
    $this->addFieldMapping('field_rcd_unit', 'unit');
    $this->addFieldMapping('field_rcd_additional_information', 'definition');
    $this->addFieldMapping('field_rcd_additional_information:format', NULL, FALSE)->defaultValue('full_html');
    $this->addFieldMapping('field_rcd_data_source', 'data_source');
    $this->addFieldMapping('field_rcd_data_source:format', NULL, FALSE)->defaultValue('full_html');
    $this->addFieldMapping('field_rcd_type_of_data_source', 'data_source_type');
    $this->addFieldMapping('field_rcd_diagram', 'id_sector')->sourceMigration('C4DRcdDiagram')
      ->description(t('Mapping id_sector in source to field_rcd_diagram'));
  }

  public function prepareRow($row) {
    // If we don't have a result, we skip this row.
    $query = Database::getConnection('default', 'legacy')->select('elementi', 'e')
      ->fields('e', [])
      ->condition('id', $row->id_result);
    $result = $query->execute()->fetch();
    if (!$result) {
      return FALSE;
    }
  }

}
