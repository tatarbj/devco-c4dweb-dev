<?php

/**
 * This class is the migration class for Links.
 */
class C4DRcdLinkMigration extends C4DRcdBaseMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->description = t('Links');

    $table_name = 'c4d_rcd_link';

    $query = Database::getConnection()->select('legacy_link', 'l')
      ->fields('l', [
        'id',
        'id_prj',
        'ele_1',
        'ele_2',
        'tipo',
      ]);

    $this->source = new MigrateSourceSQL($query, [], NULL, ['cache_counts' => TRUE]);
    $this->destination = new MigrateDestinationTable($table_name);

    $this->map = new MigrateSQLMap($this->machineName,
      [
        'id' => [
          'type' => 'int',
          'not null' => TRUE,
          'description' => 'LinkID.',
          'alias' => 'l',
        ],
      ],
      MigrateDestinationTable::getKeySchema($table_name)
    );

    $this->addFieldMapping('id_prj', 'id_prj')->sourceMigration('C4DRcdDiagram');
    $this->addFieldMapping('ele_1', 'ele_1')->sourceMigration(['C4DRcdPriorityArea', 'C4DRcdResult', 'C4DRcdImpact', 'C4DRcdFloat']);
    $this->addFieldMapping('ele_2', 'ele_2')->sourceMigration(['C4DRcdPriorityArea', 'C4DRcdResult', 'C4DRcdImpact', 'C4DRcdFloat']);
    $this->addFieldMapping('tipo', 'tipo');

  }

  public function prepareRow($row) {
    // If we don't have a project, we skip this row.
    $query = Database::getConnection()->select('legacy_progetti', 'p')
      ->fields('p', [])
      ->condition('id', $row->id_prj);
    $result = $query->execute()->fetch();
    if (!$result) {
      return FALSE;
    }
  }
}



