<?php

/**
 * This class is the base class for all migrations.
 *
 * It contains common settings and utilities.
 */
abstract class C4DRcdBaseMigration extends Migration {
  const DEST_ENTITY_TYPE = 'result_chain_diagram';
  const DEST_BUNDLE_DIAGRAM = 'diagram';
  const DEST_BUNDLE_PRIORITY_AREA = 'priority_area';
  const DEST_BUNDLE_RESULT = 'result';
  const DEST_BUNDLE_IMPACT = 'impact';
  const DEST_BUNDLE_FLOAT = 'float';
  const DEST_BUNDLE_INDICATOR = 'indicator';
  const SOURCE_ELEMENTI_TABLE_FIELDS = [
    'id',
    'id_prj',
    'vertical',
    'id_txt',
    'tipo',
    'colonna',
    'x',
    'y',
    'width',
    'height',
    'riga_1',
    'riga_2',
    'riga_3',
    'z_index',
    'bg_color',
    'contatore_z',
    'titolo',
    'descr',
    'link',
    'hovering',
    'file_pdf',
    'http_type',
    'ordine',
  ];
}
