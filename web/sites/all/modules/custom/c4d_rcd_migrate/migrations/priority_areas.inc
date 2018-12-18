<?php

/**
 * This class is the migration class for Priority Areas.
 */
class C4DRcdPriorityAreaMigration extends C4DRcdBaseMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Priority Areas');

    $query = Database::getConnection()->select('legacy_priority_area', 'p')
      ->fields('p', [
        'id',
        'id_prj',
        'descr',
        'color',
        'tipologia',
      ]);
    // Priority areas in elementi table can be identified by colonna column and
    // vertical = 1.
    $query->innerJoin('elementi', 'e', 'e.colonna = p.id AND vertical = 1');
    $query->fields('e', []);

    $this->source = new MigrateSourceSQL($query, [], NULL, ['cache_counts' => TRUE]);

    // Set up our destination.
    $this->destination = new MigrateDestinationEntityAPI(C4DRcdBaseMigration::DEST_ENTITY_TYPE, C4DRcdBaseMigration::DEST_BUNDLE_PRIORITY_AREA);

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
    $this->addFieldMapping('title', 'titolo')
      ->description(t('Mapping priority area description in source to entity title'));
    $this->addFieldMapping('field_rcd_svg_element', 'vertical');
    $this->addFieldMapping('field_rcd_svg_element:vertical', 'vertical');
    $this->addFieldMapping('field_rcd_svg_element:tipo', 'tipo');
    $this->addFieldMapping('field_rcd_svg_element:colonna', 'colonna');
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
    $this->addFieldMapping('field_rcd_svg_element:descr', 'e.descr');
    $this->addFieldMapping('field_rcd_svg_element:hovering', 'hovering');
    $this->addFieldMapping('field_rcd_svg_element:http_type', 'http_type');
    $this->addFieldMapping('field_rcd_svg_element:color', 'color');
    $this->addFieldMapping('field_rcd_svg_element:ordine', 'ordine');
//      ->description(t('Mapping elementi in source to field_rcd_svg_element'));
    $this->addFieldMapping('field_rcd_diagram', 'id_prj')->sourceMigration('C4DRcdDiagram')
      ->description(t('Mapping id_prj in source to field_rcd_diagram'));
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
  }

  public function complete($entity, stdClass $row) {
    // Update SVG element colonna with created entity's ID.
    $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['colonna'] = $entity->id;
    field_attach_update(C4DRcdBaseMigration::DEST_ENTITY_TYPE, $entity);
  }

}