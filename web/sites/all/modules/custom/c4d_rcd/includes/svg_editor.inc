<?php

/**
 * Base class for interactions with SVG objects.
 */
class SVGeditor {

  /**
   * Default width for SVG elements.
   */
  const ELEMENT_DEFAULT_WIDTH = 100;

  /**
   * Default height for SVG elements.
   */
  const ELEMENT_DEFAULT_HEIGHT = 48;

  /**
   * Elenco progetti.
   *
   * @return array
   */
  public static function elenco_progetti() {
    $results = [];
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', C4D_RCD_ENTITY_TYPE)
        ->entityCondition('bundle', C4D_RCD_BUNDLE_DIAGRAM);

    $result = $query->execute();
    if (isset($result[C4D_RCD_ENTITY_TYPE])) {
      $items = array_keys($result[C4D_RCD_ENTITY_TYPE]);
      $items = entity_load(C4D_RCD_ENTITY_TYPE, $items);
      foreach ($items as $item) {
        $results[] = SVGeditor::mapEntityFieldsToArray($item);
      }
    }
    return $results;
  }

  /**
   * Questa serve a gestire l'elenco delle priority area.
   *
   * @param int $id_prj
   * @return array
   */
  public static function elenco_priority_area($id_prj) {
    $results = [];
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', C4D_RCD_ENTITY_TYPE)
        ->entityCondition('bundle', C4D_RCD_BUNDLE_PRIORITY_AREA)
        ->fieldCondition('field_rcd_diagram', 'target_id', $id_prj);

    $result = $query->execute();
    if (isset($result[C4D_RCD_ENTITY_TYPE])) {
      $items = array_keys($result[C4D_RCD_ENTITY_TYPE]);
      $items = entity_load(C4D_RCD_ENTITY_TYPE, $items);
      foreach ($items as $item) {
        $results[] = SVGeditor::mapEntityFieldsToArray($item);
      }
    }
    return $results;
  }

  /**
   * Questa � la parte che gestisce il salvataggio delle posizioni.
   *
   * @param int $id_prj
   * @param int $area_select
   * @return array
   */
  public static function load_positions($id_prj, $area_select) {
    $diagram = _c4d_rcd_load_full_diagram($id_prj, $area_select);
    $arr_result = [];
    $arr_result['transform'] = [];

    if (!is_object($diagram['diagram'])) {
      $arr_result['stato'] = 0;
      $arr_result['msg'] = "Attenzione devi prima selezionare un progetto";
      return $arr_result;
    }
    else {
      $arr_result['transform'] = SVGeditor::mapEntityFieldsToArray($diagram['diagram']);
    }

    $arr_result['elementi'] = [];
    $arr_result['link'] = [];


    // Questo � il pezzo in cui legge gli elementi e scrive il json.
    $element_types = ['priority_areas', 'results', 'floats', 'impacts'];
    foreach ($element_types as $type) {
      foreach ($diagram[$type] as $item) {
        $arr_result['elementi'][] = SVGeditor::mapEntityFieldsToArray($item);
      }
    }

    // Questa � la parte che gestisce l'invio dei link.
    foreach ($diagram['links'] as $ele) {

      $tipo = (!$ele['tipo']) ? 0 : 1;
      $arr_result['link'][] = [
        'ele1' => $ele['ele_1'],
        'ele2' => $ele['ele_2'],
        'tipo' => $tipo
      ];
    }
    return $arr_result;
  }

  /**
   * Questa serve ad aggiornare l'elemento.
   *
   * @param type $colonna
   * @param type $bg_color
   * @param type $titolo
   * @param type $descr
   * @param type $id_ele
   * @param type $link_ele
   * @param type $http_type
   * @param type $vertical
   * @param type $hovering
   * @param type $ordine
   * @return boolean
   */
  public static function update_element($colonna, $bg_color, $titolo, $descr, $id_ele, $link_ele, $http_type, $vertical, $hovering, $ordine) {
    $return_val = TRUE;

    // Load the item.
    $entity = NULL;
    $entities = entity_load(C4D_RCD_ENTITY_TYPE, [$id_ele]);
    if (!$entity = array_pop($entities)) {
      $return_val = FALSE;
    }

    if ($entity) {
      $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['colonna'] = $colonna;
      $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['color'] = $bg_color;
      $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['titolo'] = $titolo;
      $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['descr'] = $descr;
      $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['link'] = $link_ele;
      $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['http_type'] = $http_type;
      $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['hovering'] = $hovering;
      $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['ordine'] = $ordine;
      field_attach_update(C4D_RCD_ENTITY_TYPE, $entity);
      $entity->title = _c4d_rcd_generate_title($entity);
      entity_save(C4D_RCD_ENTITY_TYPE, $entity);
    }

    return $return_val;
  }

  /**
   * [Description not provided]
   *
   * @param int $id_record
   * @param int $width
   * @param int $height
   * @param int $x
   * @param int $y
   * @return boolean
   */
  public static function update_element2($id_record, $width, $height, $x, $y) {
    $entities = entity_load(C4D_RCD_ENTITY_TYPE, [$id_record]);
    if ($entity = array_pop($entities)) {
      $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['x'] = $x;
      $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['y'] = $y;
      $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['width'] = $width;
      $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['height'] = $height;
      field_attach_update(C4D_RCD_ENTITY_TYPE, $entity);
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Questa � la parte che gestisce.
   */
  public static function save_position($tipologia, $titolo, $bg_color, $colonna, $descr, $id_prj, $link, $vertical, $hovering = '', $http_type, $ordine) {
    $arr_output = [];

    // Define element bundle.
    $bundle = '';
    if ($vertical == 1) {
      $bundle = C4D_RCD_BUNDLE_PRIORITY_AREA;
    }
    else {
      switch ($colonna) {
        case 12:
          $bundle = C4D_RCD_BUNDLE_FLOAT;
          break;
        case 13:
          $bundle = C4D_RCD_BUNDLE_IMPACT;
          break;
        default:
          $bundle = C4D_RCD_BUNDLE_RESULT;
          break;
      }
    }

    // Create the new element.
    $entity = entity_create(C4D_RCD_ENTITY_TYPE, ['type' => $bundle]);
    $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['titolo'] = $titolo;
    $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['colonna'] = $colonna;
    $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['color'] = $bg_color;
    $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['width'] = SVGeditor::ELEMENT_DEFAULT_WIDTH;
    $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['height'] = SVGeditor::ELEMENT_DEFAULT_HEIGHT;
    $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['descr'] = $descr;
    $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['link'] = $link;
    $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['http_type'] = $http_type;
    $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['vertical'] = $vertical;
    $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['hovering'] = $hovering;
    $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['ordine'] = $ordine;
    $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['tipo'] = 0;
    $entity->field_rcd_diagram[LANGUAGE_NONE][0]['target_id'] = $id_prj;
    $entity->field_rcd_priority_area[LANGUAGE_NONE][0]['target_id'] = $colonna;
    $entity->title = _c4d_rcd_generate_title($entity);
    $entity->save();
    field_attach_update(C4D_RCD_ENTITY_TYPE, $entity);

    $arr_output['id'] = $entity->id;
    $arr_output['ordine'] = $ordine;
    $arr_output['bg_color'] = $bg_color;
    $arr_output['colonna'] = $colonna;
    $arr_output['riga_1'] = '';
    $arr_output['riga_2'] = '';
    $arr_output['riga_3'] = '';
    $arr_output['titolo'] = $titolo;
    $arr_output['descr'] = $descr;
    $arr_output['link'] = $link;
    $arr_output['http_type'] = $http_type;
    $arr_output['vertical'] = $vertical;
    $arr_output['hovering'] = $hovering;

    return $arr_output;
  }

  /**
   * Questa serve a salvare le posizioni.
   *
   * @param int $area_select
   * @param int $id_prj
   * @param array $elementi
   * @param array $link
   * @param string $transform
   * @return array
   */
  public static function save_positions($area_select, $id_prj, $elementi, $link, $transform) {
    // We need to make sure multiple requests don't interfere between them.
    // So we get a lock to be sure we don't have concurrent requests.
    if (!lock_acquire('svg_editor__save_positions')) {
      lock_wait('svg_editor__save_positions');
      return SVGeditor::save_positions($area_select, $id_prj, $elementi, $link, $transform);
    }

    $arr_return = [];
    $entities = entity_load(C4D_RCD_ENTITY_TYPE, [$id_prj]);
    if (!$entity = array_pop($entities)) {
      $arr_return['stato'] = 0;
      $arr_return['msg'] = "Attenzione devi prima selezionare un progetto";
      return $arr_return;
    }
    // Questa � la parte che salva la trasformazione.
    elseif (count($entities) == 1 && $transform != "") {
      $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['matrix'] = $transform;
      field_attach_update(C4D_RCD_ENTITY_TYPE, $entity);
    }

    // Questo � l'update sugli elementi.
    foreach ($elementi as $key => $val) {
      $entities = entity_load(C4D_RCD_ENTITY_TYPE, [$val['id']]);
      if (!$entity = array_pop($entities)) {
        continue;
      }

      $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['x'] = $val['x'];
      $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['y'] = $val['y'];
      $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['width'] = $val['width'];
      $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['height'] = $val['height'];
      if (isset($val['colonna'])) {
        $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['colonna'] = $val['colonna'];
      }
      if (isset($val['bg_color'])) {
        $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['color'] = $val['bg_color'];
      }
      if (isset($val['contatore_z'])) {
        $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['contatore_z'] = $val['contatore_z'];
      }
      field_attach_update(C4D_RCD_ENTITY_TYPE, $entity);
    }

    // Quindi ci sono due casistiche, una con la colonna selezionata, l'altra
    // senza la colonna selezionata di conseguenza i check vanno fatti su tutto
    // il proj o solo sulle parti collegate con la colonna selezionata questo �
    // il bla bla bla.
    if (isset($link)) {
      $diagram = _c4d_rcd_load_full_diagram($id_prj, $area_select);

      $arr_elementi = [];

      // Get elements array.
      foreach ($diagram as $child_type => $items) {
        if (!in_array($child_type, ['priority_areas', 'results', 'floats', 'impacts'])) {
          continue;
        }
        foreach ($items as $item) {
          $arr_elementi[$item->id] = TRUE;
        }
      }

      // Get links array.
      $arr_link = [];
      foreach ($diagram['links'] as $item_id => $item) {
        $arr_link[] = ['id' => $item['id'], 'ele_1' => $item['ele_1'], 'ele_2' => $item['ele_1']];
      }

      // Io in questo caso gestisco l'inserimento.
      foreach ($link as $key => $val) {
        $ele1 = $val['ele1'];
        $ele2 = $val['ele2'];
        $tipo_link = $val['tipo'];

        // Prima devo fare il check per vedere se appartiene agli elementi del
        // progetto.
        if (($ele1 != $ele2) && (isset($arr_elementi[$ele1]) && isset($arr_elementi[$ele2]))) {

          // Ora devo fare il check per sapere se � gi� presente.
          $trovato = FALSE;

          foreach ($arr_link as $key1 => $value1) {
            $e1 = $value1['ele_1'];
            $e2 = $value1['ele_2'];

            if (($ele1 == $e1 && $ele2 == $e2) || ($ele1 == $e2 && $ele2 == $e1)) {
              $trovato = TRUE;
            }
          }

          if ($trovato == FALSE) {
            db_insert('c4d_rcd_link')
                ->fields([
                  'id_prj' => $id_prj,
                  'ele_1' => $ele1,
                  'ele_2' => $ele2,
                  'tipo' => $tipo_link,
                ])
                ->execute();
          }
        }
      }

      // Reload the diagram (to get all new links?).
      $diagram = _c4d_rcd_load_full_diagram($id_prj, $area_select);
      foreach ($diagram['links'] as $item) {
        $arr_link[] = ['id' => $item['id'], 'ele_1' => $item['ele_1'], 'ele_2' => $item['ele_2']];
      }

      // In questo caso gestisco la cancellazione.
      foreach ($arr_link as $key => $value) {

        $e1 = $value['ele_1'];
        $e2 = $value['ele_2'];
        $id_link = $value['id'];

        $trovato = FALSE;

        // Questa � il foreach dell'elenco.
        foreach ($link as $key => $val) {
          $ele1 = $val['ele1'];
          $ele2 = $val['ele2'];

          if (($ele1 == $e1 && $ele2 == $e2) || ($ele1 == $e2 && $ele2 == $e1)) {
            $trovato = TRUE;
          }
        }

        if ($trovato == FALSE) {
          db_delete('c4d_rcd_link')->condition('id', $id_link)->execute();
        }
      }
    }

    lock_release('svg_editor__save_positions');
    return $arr_return;
  }

  /**
   * Questa � la parte che gestisce il dettaglio.
   *
   * @param int $id_record
   * @return array
   */
  public static function dettaglio_elemento($id_record) {
    $result_item = NULL;
    $entities = entity_load(C4D_RCD_ENTITY_TYPE, [$id_record]);
    if ($entity = array_pop($entities)) {
      $result_item = SVGeditor::mapEntityFieldsToArray($entity);
    }
    return $result_item;
  }

  /**
   * Questa serve ad eliminare i progetti.
   *
   * @param int $id_record
   * @return string
   */
  public static function elimina_ele($id_record) {
    $entities = entity_load(C4D_RCD_ENTITY_TYPE, [$id_record]);
    $arr = [];
    if (!$entity = array_pop($entities)) {
      $arr['esito'] = 0;
      $arr['descr'] = "Errore nella cancellazione.";
    }

    $vertical = $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['vertical'];
    $id_colonna = $entity->field_rcd_svg_element[LANGUAGE_NONE][0]['colonna'];

    if ($vertical == "0") {

      entity_delete(C4D_RCD_ENTITY_TYPE, $entity->id);
      // Ora devo cancellare gli indicatori associati.
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', C4D_RCD_ENTITY_TYPE)
          ->entityCondition('bundle', C4D_RCD_BUNDLE_INDICATOR)
          ->fieldCondition('field_rcd_result', 'target_id', $id_record);
      $result = $query->execute();
      if (isset($result[C4D_RCD_ENTITY_TYPE])) {
        $items = array_keys($result[C4D_RCD_ENTITY_TYPE]);
        entity_delete_multiple(C4D_RCD_ENTITY_TYPE, $items);
      }

      $arr['esito'] = 1;
      $arr['descr'] = "Cancellazione avvenuta con successo.";
    }
    elseif ($vertical == "1") {

      // Prima devo fare il check per capire se esistono result associati a
      // quella categoria se ci sono non si fa nulla.
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', C4D_RCD_ENTITY_TYPE)
          ->fieldCondition('field_rcd_svg_element', 'colonna', $entity->id)
          ->fieldCondition('field_rcd_svg_element', 'vertical', 0);

      $result = $query->execute();
      $num = count($result[C4D_RCD_ENTITY_TYPE]);

      $arr = [];
      $arr['esito'] = 0;
      $arr['descr'] = "Errore nella cancellazione.";

      if (!$num) {
        entity_delete(C4D_RCD_ENTITY_TYPE, $entity->id);
        $arr['esito'] = 1;
        $arr['descr'] = "Cancellazione avvenuta con successo.";
      }
      else {
        $arr['esito'] = 0;
        $arr['descr'] = "La categoria non puo essere cancellata perche ci sono dei result associati.";
      }
    }

    return $arr;
  }

  /**
   * Questa serve a predere il dettaglio del record.
   *
   * @param int $id
   * @return array
   */
  public static function dettaglio($id) {
    $result_item = NULL;
    $entities = entity_load(C4D_RCD_ENTITY_TYPE, [$id]);
    if ($entity = array_pop($entities)) {
      $result_item = SVGeditor::mapEntityFieldsToArray($entity);
    }
    return $result_item;
  }

  /**
   * Helper function to map object fields (mainly SVG element field) to a flat
   * array.
   * This is needed for legacy JS scripts.
   *
   * @param object $entity
   * @return array
   */
  public static function mapEntityFieldsToArray($entity) {
    $result = [];
    $result['id'] = $entity->id;

    // SVG element field.
    if (isset($entity->field_rcd_svg_element[LANGUAGE_NONE][0])) {
      foreach ($entity->field_rcd_svg_element[LANGUAGE_NONE][0] as $field_name => $value) {
        switch ($field_name) {
          case 'color':
            $result['color'] = empty($value) ? NULL : $value;
            $result['bg_color'] = empty($value) ? NULL : $value;
            break;

          case 'tipo':
            $result['tipologia'] = (string) $value;
            break;

          case 'riga_1':
          case 'riga_2':
          case 'riga_3':
            $result['text'][] = $value;
            break;

          default:
            $result[$field_name] = $value;
            break;
        }
      }
    }

    // Matrix field.
    if (isset($entity->field_rcd_matrix[LANGUAGE_NONE][0]['value']) && !empty($entity->field_rcd_matrix[LANGUAGE_NONE][0])) {
      $result['matrix'] = $entity->field_rcd_matrix[LANGUAGE_NONE][0]['value'];
    }

    // Specific properties.
    switch ($entity->type) {
      case C4D_RCD_BUNDLE_DIAGRAM:
        $result['id'] = $entity->id;
        $result['identificativo'] = $entity->title;
        break;

      case C4D_RCD_BUNDLE_PRIORITY_AREA:
        $result['id'] = $entity->id;
        $result['id_prj'] = $entity->field_rcd_diagram[LANGUAGE_NONE][0]['target_id'];
        $result['tipologia'] = 0;
        $result['descr'] = $entity->title;
        // SVG editor expects colors for priority areas to be in uppercase.
        $result['color'] = strtoupper($result['color']);
        $result['bg_color'] = strtoupper($result['bg_color']);
        break;

      case C4D_RCD_BUNDLE_RESULT:
     // Load priority area.
        $query = new EntityFieldQuery();
        $query->entityCondition('entity_type', C4D_RCD_ENTITY_TYPE)
            ->entityCondition('bundle', C4D_RCD_BUNDLE_PRIORITY_AREA)
            ->entityCondition('entity_id', $entity->field_rcd_priority_area[LANGUAGE_NONE][0]['target_id']);
        $results = $query->execute();
        if (isset($results[C4D_RCD_ENTITY_TYPE])) {
          $items = array_keys($results[C4D_RCD_ENTITY_TYPE]);
          $items = entity_load(C4D_RCD_ENTITY_TYPE, $items);
          $priority_area = array_pop($items);
          // We need to add the diagram ID, grab it from database.
          $result['id_prj'] = $priority_area->field_rcd_diagram[LANGUAGE_NONE][0]['target_id'];
        }
        break;
    }
    return $result;
  }

}
