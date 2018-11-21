<?php

/**
 * This class is the migration class for Diagrams.
 */
class C4DRcdDiagramMigration extends C4DRcdBaseMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Diagrams');

    $query = Database::getConnection('default', 'legacy')->select('progetti', 'p')
      ->fields('p', [
        'id',
        'identificativo',
        'matrix',
      ]);

    $this->source = new MigrateSourceSQL($query, [], NULL, ['cache_counts' => TRUE]);

    // Set up our destination.
    $this->destination = new MigrateDestinationEntityAPI(C4DRcdBaseMigration::DEST_ENTITY_TYPE, C4DRcdBaseMigration::DEST_BUNDLE_DIAGRAM);

    $this->map = new MigrateSQLMap($this->machineName,
      [
        'id' => [
          'type' => 'int',
          'not null' => TRUE,
          'description' => 'Diagram ID.',
          'alias' => 'p',
        ],
      ],
      MigrateDestinationEntityAPI::getKeySchema(C4DRcdBaseMigration::DEST_ENTITY_TYPE)
    );

    // Mapped fields
    $this->addFieldMapping('title', 'identificativo')
      ->description(t('Mapping diagram name in source to entity title'));
    $this->addFieldMapping('field_rcd_matrix', 'matrix')
      ->description(t('Mapping matrix in source to field_rcd_matrix'));
  }
}