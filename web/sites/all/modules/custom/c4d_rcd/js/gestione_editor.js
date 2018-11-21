$ = jQuery;

$.fn.serializefiles = function () {
  var obj = $(this);
  /* ADD FILE TO PARAM AJAX */
  var formData = new FormData();
  $.each($(obj).find("input[type='file']"), function (i, tag) {
    $.each($(tag)[0].files, function (i, file) {
      formData.append(tag.name, file);
    });
  });
  var params = $(obj).serializeArray();
  $.each(params, function (i, val) {
    formData.append(val.name, val.value);
  });
  return formData;
};

/**
 * Replacement function for jQuery's addClass() function which doesn't work with
 * SVG elements when using jQuery < 3.x
 */
$.fn.addSvgClass = function (className) {
  var classes = this.attr("class").split(' ');
  var index = classes.indexOf(className);
  if (index < 0) {
    classes.push(className);
    this.attr("class", classes.join(' '));
  }
};

/**
 * Replacement function for jQuery's removeClass() function which doesn't work
 * with SVG elements when using jQuery < 3.x
 */
$.fn.removeSvgClass = function (className) {
  var classes = this.attr("class").split(' ');
  var index = classes.indexOf(className);
  if (index > -1) {
    classes.splice(index, 1);
    this.attr("class", classes.join(' '));
  }
};

/**
 * Replacement function for jQuery's hasClass() function which doesn't work with
 * SVG elements when using jQuery < 3.x
 */
$.fn.hasSvgClass = function (className) {
  var classes = this.attr("class").split(' ');
  var index = classes.indexOf(className);
  if (index < 0) {
    return false;
  }
  return true;
};

function sleepFor(sleepDuration) {
  var now = new Date().getTime();
  while (new Date().getTime() < now + sleepDuration) { /* do nothing */
  }
}

// Istruzioni menu contestuale: 
// https://github.com/dgoguerra/bootstrap-menu
var menu = new BootstrapMenu('#drawing', {
  actionsGroups: [
    ['simple_line', 'dotted_line'],
    ['remove_element', 'modify_element', 'pop_on_top', 'refresh_element']
  ],
  actions: {
    add_vertical: {
      name: 'Add Priority Area',
      // iconClass: 'fa-pencil',
      onClick: function () {
        svg_obj.aggiungi_vertical();
      },
      isEnabled: function (row) {
        var id_prj = $('#prj_id').val();
        if (id_prj != "0")
          return true;
        else
          return false;
      }
    },
    add_element: {
      name: 'Add Result',
      onClick: function () {
        svg_obj.aggiungi_elemento();
      },
      isEnabled: function (row) {
        var id_prj = $('#prj_id').val();
        if (id_prj != "0")
          return true;
        else
          return false;
      }
    },
    float_text: {
      name: 'Add Float Text',
      onClick: function () {
        svg_obj.aggiungi_scritta_float();
      },
      isEnabled: function (row) {
        var id_prj = $('#prj_id').val();
        if (id_prj != "0")
          return true;
        else
          return false;
      }
    }
    ,
    add_impact: {
      name: 'Add Impact',
      onClick: function () {
        svg_obj.aggiungi_impact();
      },
      isEnabled: function (row) {
        var id_prj = $('#prj_id').val();
        if (id_prj != "0")
          return true;
        else
          return false;
      }
    },
    simple_line: {
      name: 'Add/Remove Line',
      onClick: function () {
        svg_obj.aggiungi_link('0');
      },
      isEnabled: function (row) {

        var ele_1 = ele_2 = vert_1 = vert_2 = "";

        var id_prj = $('#prj_id').val();
        if (id_prj != "0") {
          // Ora devo controllare che siano stati selezionati due elementi
          var quanti = $('.svg_select').length;
          if (quanti == "2") {

            var vert_1 = vert_2 = colonna_1 = colonna_2 = "";
            var id_1 = id_2 = 0;
            $('.svg_select').each(function (index, value) {
              var id_sel = value.id;
              console.log('id_elemento_select : ' + value.id);
              var id_vert = $('#' + id_sel).attr('vertical');
              var n_colonna = $('#' + id_sel).attr('colonna');

              if (!id_1)
                id_1 = id_sel;
              else
                id_2 = id_sel

              if (!vert_1)
                vert_1 = id_vert;
              else
                vert_2 = id_vert;

              if (!colonna_1)
                colonna_1 = n_colonna;
              else
                colonna_2 = n_colonna;
            });


            if (colonna_1 != "100" && colonna_2 != "100" && vert_1 == "0" && vert_2 == "0") {
              // Va controllato se gi� esiste una linea
              console.log('Linea singola array righe', svg_obj.json_data);
              tipo_dato = 3;

              for (x = 0; x < svg_obj.json_data.link.length; x++) {
                var valore_1 = svg_obj.json_data.link[x].ele1;
                var valore_2 = svg_obj.json_data.link[x].ele2;

                if ((valore_1 == id_1 && valore_2 == id_2) || (valore_1 == id_2 && valore_2 == id_1)) {
                  tipo_dato = svg_obj.json_data.link[x].tipo;
                }

              }

              console.log('tipo_linea', tipo_dato);

              // Tratteggiata => 1 ; continua = 0
              if (tipo_dato == 1) {
                return false;
              }


              return true;
            } else
              return false;
          } else
            return false;
        } else
          return false;
      }
    },
    dotted_line: {
      name: 'Add/Remove dotted Line',
      onClick: function () {
        svg_obj.aggiungi_link('1');
      },
      isEnabled: function (row) {
        var id_prj = $('#prj_id').val();
        if (id_prj != "0") {
          // Ora devo controllare che siano stati selezionati due elementi
          var quanti = $('.svg_select').length;
          if (quanti == "2") {
            var vert_1 = vert_2 = colonna_1 = colonna_2 = "";
            var id_1 = id_2 = 0;
            $('.svg_select').each(function (index, value) {

              var id_sel = value.id;
              console.log('id_elemento_select : ' + value.id);
              var id_vert = $('#' + id_sel).attr('vertical');
              var n_colonna = $('#' + id_sel).attr('colonna');

              if (!id_1)
                id_1 = id_sel;
              else
                id_2 = id_sel

              if (!vert_1)
                vert_1 = id_vert;
              else
                vert_2 = id_vert;

              if (!colonna_1)
                colonna_1 = n_colonna;
              else
                colonna_2 = n_colonna;

            });

            if (colonna_1 != "100" && colonna_2 != "100" && vert_1 == "0" && vert_2 == "0") {

              console.log('Linea singola array righe', svg_obj.json_data);
              tipo_dato = 3;

              for (x = 0; x < svg_obj.json_data.link.length; x++) {
                var valore_1 = svg_obj.json_data.link[x].ele1;
                var valore_2 = svg_obj.json_data.link[x].ele2;

                if ((valore_1 == id_1 && valore_2 == id_2) || (valore_1 == id_2 && valore_2 == id_1)) {
                  tipo_dato = svg_obj.json_data.link[x].tipo;
                }

              }

              console.log('tipo_linea', tipo_dato);

              // Tratteggiata => 1 ; continua = 0
              if (tipo_dato == 0) {
                return false;
              }


              return true;
            } else
              return false;
          } else
            return false;
        } else
          return false;
      }
    },
    modify_element: {
      name: 'Modify element',
      iconClass: 'glyphicon glyphicon-pencil',
      onClick: function () {
        svg_obj.modifica_elemento();
      },
      isEnabled: function (row) {
        var id_prj = $('#prj_id').val();
        if (id_prj != "0") {
          // Ora devo controllare che siano stati selezionati due elementi
          var quanti = $('.svg_select').length;
          if (quanti == "1")
            return true
          else
            return false;
        } else
          return false;
      }
    },
    remove_element: {
      name: 'Remove element',
      iconClass: 'glyphicon glyphicon-remove',
      onClick: function () {
        svg_obj.elimina_elemento();
      },
      isEnabled: function (row) {
        var id_prj = $('#prj_id').val();
        if (id_prj != "0") {
          // Ora devo controllare che siano stati selezionati due elementi
          var quanti = $('.svg_select').length;
          if (quanti == "1")
            return true
          else
            return false;
        } else
          return false;
      }
    }
    ,
    pop_on_top: {
      name: 'Bring to front',
      iconClass: 'glyphicon glyphicon-arrow-up',
      onClick: function () {
        svg_obj.zindex_top();
      },
      isEnabled: function (row) {
        var id_prj = $('#prj_id').val();
        if (id_prj != "0") {
          // Ora devo controllare che siano stati selezionati due elementi
          var quanti = $('.svg_select').length;
          if (quanti == "1")
            return true
          else
            return false;
        } else
          return false;
      }
    },
    refresh_element: {
      name: 'Refresh ',
      iconClass: 'glyphicon glyphicon-refresh',
      onClick: function () {
        svg_obj.cambia_prj($('#prj_id').val());
      },
      isEnabled: function (row) {
        return true;
      }
    }
  }
});

function deltaTransformPoint(matrix, point) {
  var dx = point.x * matrix.a + point.y * matrix.c + 0;
  var dy = point.x * matrix.b + point.y * matrix.d + 0;
  return {x: dx, y: dy};
}

// @see https://gist.github.com/2052247
function decomposeMatrix() {

  matrix = document.getElementById('contenitore_main').getCTM();

  // calculate delta transform point
  var px = deltaTransformPoint(matrix, {x: 0, y: 1});
  var py = deltaTransformPoint(matrix, {x: 1, y: 0});

  // calculate skew
  var skewX = ((180 / Math.PI) * Math.atan2(px.y, px.x) - 90);
  var skewY = ((180 / Math.PI) * Math.atan2(py.y, py.x));

  return {
    translateX: parseInt(matrix.e),
    translateY: parseInt(matrix.f),
    scaleX: parseFloat(Math.sqrt(matrix.a * matrix.a + matrix.b * matrix.b).toFixed(3)),
    scaleY: parseFloat(Math.sqrt(matrix.c * matrix.c + matrix.d * matrix.d).toFixed(3)),
    skewX: skewX,
    skewY: skewY,
    rotation: skewX // rotation is the same as skew x 
  };
}

var draw_main = SVG('drawing').size('100%', '700')
draw_main.id('contenitore_main1');

var draw = draw_main.group();
draw.id('contenitore_main');

draw_main.on("mousedown", function (d) {

  var valore = d.which;
  // questo perch� se il tasto non � quello deve effettuare il reset
  if (valore == "3") {

    var matrice = decomposeMatrix();
    var pt = {'x': 0, 'y': 0};
    pt.x = (d.clientX - matrice.translateX) / matrice.scaleX;
    ;

    // 100 rappresenta l'altezza del menu e dei bottoni
    pt.y = (d.clientY - matrice.translateY - 100) / matrice.scaleX;
    ;
    svg_obj.right_click_pt = pt;

    console.log('*** Matrix svg', matrice);
    console.log('Right click: ', pt);
  }

});

var draw_container1 = document.getElementById("contenitore_main1");
var draw_container = document.getElementById("contenitore_main");

var svg_obj = {
  right_click_pt: 0,
  cambiamento_stato: false,
  arr_linked: [],
  spessore_bordo: '1px',
  colore_border: 'rgb(0,0,0)',
  colore_area_arr: [],
  color_specific_element_arr: [],
  angle: function (cx, cy, ex, ey) {
    var dy = ey - cy;
    var dx = ex - cx;
    var theta = Math.atan2(dy, dx); // range (-PI, PI]
    theta *= 180 / Math.PI; // rads to degs, range (-180, 180]

    return theta;
  }
  ,
  json_data: [], // questo � il json preso dal file
  arr_elementi: [], // questo contiene gli elementi con la posizione
  arr_righe: [], // questo dovrebbe contenere in seguito le righe
  init: function () {
    // Colors for float text and impact elements were retrieved from the
    // priority areas table in legacy application.
    // This is too messy for our module, so we define them here.
    this.color_specific_element_arr[12] = '#efefef';
    this.color_specific_element_arr[13] = '#fff';
    this.colore_area_arr[12] = '#efefef';
    this.colore_area_arr[13] = '#fff';

    //this.riempi_array_colori() ; 
    this.carica_progetti();
    setInterval(svg_obj.aggiorna_stato, 3000);
  }
  ,
  // Questa serve ad aggiornare lo stato 
  aggiorna_stato: function () {
    if (svg_obj.cambiamento_stato) {
      svg_obj.salva_posizioni();
    }
  }
  ,
  // questa serve a trovare il legame tra gli elementi
  // arr_elementi
  effettua_link: function () {
    svg_obj.arr_linked = [];

    var numero = $('.svg_select').length;
    if (numero == 1) {
      var id_select = $('.svg_select').attr('id');
      svg_obj.arr_linked.push(id_select);
      this.trova_link(id_select, 'right');
      this.trova_link(id_select, 'left');

      $('.svg_select').removeSvgClass("svg_select");

      $.each(svg_obj.arr_linked, function (index, value) {
        console.log(value);
        $('#' + value).addSvgClass("svg_link");
      });
    }
  }
  ,
  // Questa serva  trovare un link
  trova_link: function (id_elemento, tipologia) {
    console.log('trova link -> id_elemento', id_elemento);
    id_elemento = parseInt(id_elemento);

    if (tipologia == "right") {
      $.each(svg_obj.arr_elementi[id_elemento].right, function (index, value) {
        if (value) {
          svg_obj.arr_linked.push(value);
          svg_obj.trova_link(value, tipologia);
        }
      });
    } else {
      $.each(svg_obj.arr_elementi[id_elemento].left, function (index, value) {
        if (value) {
          svg_obj.arr_linked.push(value);
          svg_obj.trova_link(value, tipologia);
        }
      });
    }
  }
  ,
  resize_selected: function () {
    var numero = $('.svg_select').length;
    if (numero > 1) {
      var width_max = 0;
      $('.svg_select').each(function (index, value) {
        // var id_ele = $('#' + value.id).attr('id');

        var width_ele = parseInt($('#' + value.id + ' rect').attr('width'));
        if (width_max < width_ele)
          width_max = width_ele;
        // console.log('Width elementi ' , width_ele); 
      });

      $('.svg_select').each(function (index, value) {
        $('#' + value.id + ' rect').attr('width', width_max);
      });

      // salvataggio
      sleepFor(1000);
      svg_obj.salva_posizioni_immediate();
      sleepFor(1000);
      // refresh
      svg_obj.cambia_prj($('#prj_id').val());
    }

  }
  ,
  align_selected: function (mode_align) {
    // mode -> left , top
    var numero = $('.svg_select').length;
    if (numero > 1) {

      var x_pos = y_pos = 0;
      arr = [];
      $('.svg_select').each(function (index, value) {
        arr[index] = {'id': value.id, 'x': $('#' + value.id).attr('x'), 'y': $('#' + value.id).attr('y')};
      });

      console.log('array elementi', arr);
      var x_att = y_att = 0;

      // Questa � la parte che gestisce 
      for (x = 0; x < arr.length; x++) {
        x_att = parseInt(arr[x].x);
        y_att = parseInt(arr[x].y);

        if (x == 0) {
          x_pos = x_att;
          y_pos = y_att;
        } else {
          if (x_pos > x_att)
            x_pos = x_att;
          if (y_pos > y_att)
            y_pos = y_att;
        }
      }

      // ora devo posizionare gli oggetti sullo stage in base all mode_align
      for (x = 0; x < arr.length; x++) {

        x_att = parseInt(arr[x].x);
        y_att = parseInt(arr[x].y);
        id_att = parseInt(arr[x].id);

        if (mode_align == "left") {
          $('#' + id_att).attr('x', x_pos);
        } else if (mode_align == "top") {
          $('#' + id_att).attr('y', y_pos);
        }
      }

      // salvataggio
      sleepFor(1000);
      svg_obj.salva_posizioni_immediate();
      sleepFor(1000);
      // refresh
      svg_obj.cambia_prj($('#prj_id').val());
    }
  }
  ,
  // questa serev acambiare il projetto
  cambia_prj: function (id_prj) {
    $('#contenitore_main').html('');
    this.json_data = [];
    this.arr_elementi = [];
    this.arr_righe = [];
    arr = [];
    arr[0] = 0;
    arr[1] = 3.50;
    draw.panZoom({'zoom': arr});

    console.log('Function -> cambia_prj -> Gestione della select cambio prj.');


    if (id_prj != "0") {
      this.get_json(id_prj);
      this.aggiorna_priority_area(id_prj, 'area_select');
      svg_obj.aggiorna_scritta_zoom();
    }
  }
  ,
  select_area: function (id_area_select) {
    // prima svuoto tutto 
    $('#contenitore_main').html('');
    var id_prj = $('#prj_id').val();
    this.json_data = [];
    this.arr_elementi = [];
    this.arr_righe = [];
    if (id_prj != "0") {
      this.get_json(id_prj);
    }
  }
  ,
  carica_progetti: function () {
    $.ajax({
      url: '/c4d_rcd/ajax/elenco_progetti',
      type: 'POST',
      cache: false,
      context: this,
      dataType: 'json',
      success: function (json) {
        $.each(json, function (index, value) {
          $('#prj_id').append('<option value="' + value.id + '">' + value.identificativo + '</option>');
        });
      }
      ,
      error: function () {
        console.log('Errore nel caricamento ajax dell\'elenco progetti');
      }
    });
  }
  ,
  // Questa va modificata e va aggiunto lo zoom ed il pan
  get_json: function (id_prj) {
    $.ajax({
      cache: false,
      type: 'POST',
      context: this,

      url: '/c4d_rcd/ajax/load_positions',
      data: {area_select: $('#area_select').val(), 'id_prj': id_prj},
      dataType: 'json',
      success: function (json) {
        console.log('**** JSON ELEMENTI ', json)
        var matrix = json['transform']['matrix'];
        console.log(matrix);

        if (matrix)
          $('#contenitore_main').attr('transform', matrix);
        else
          $('#contenitore_main').attr('transform', '');
        this.json_data = json;
        this.crea_elementi();
      },
      error: function () {
        console.log('Errore nella chiamata ajx');
      }
    });
  }
  ,
  colore_area: function (area) {
    if (!(area in this.colore_area_arr)) {
      return this.color_specific_element_arr[area];
    }
    return this.colore_area_arr[area];
  }
  ,
  //  questa � la funzione che aggiunge_le'elemento all'svg, e sar� unica 
  aggiungi_elemento_svg: function (id_record, titolo, descr, width, height, s_x, s_y, bg_color, colonna, vertical) {

    var nested = draw.nested();

    nested.x(s_x);
    nested.y(s_y);

    if (!titolo)
      titolo = " ";
    if (!descr)
      descr = " ";
    var arr_titolo = titolo.split("\n");
    var arr_descr = descr.split("\n");

    var dim_carattere = 13;
    var dim_carattere_vert = 14;
    var dim_carattere_float = 16;

    var titolo_ele = nested.text(function (add) {
      contatore = 0;
      if (vertical == "0") {

        for (z = 0; z < arr_titolo.length; z++) {
          if (arr_titolo[z] != "") {
            add.tspan(arr_titolo[z]).addClass('stile_testo_titolo').newLine();
          }
        }
        add.tspan(' ').newLine();

        for (z = 0; z < arr_descr.length; z++) {
          if (arr_descr[z] != "") {
            add.tspan(arr_descr[z]).newLine();
          }
        }
      } else {

        for (z = 0; z < arr_titolo.length; z++) {
          if (arr_titolo[z] != "") {
            add.tspan(arr_titolo[z]).attr("text-anchor", "middle").addClass('stile_testo_titolo').newLine();
            // text-anchor="middle"
          }
        }
      }

    }).attr({'fill': '#333'});

    if (vertical == "0") {

      if (colonna == "12") {
        titolo_ele.font({
          family: 'tahoma',
          size: dim_carattere_float,
          leading: 1
        });
      } else {
        titolo_ele.font({
          family: 'tahoma',
          size: dim_carattere,
          leading: 1
        });
      }
    } else {
      titolo_ele.font({
        family: 'tahoma',
        size: dim_carattere_vert,
        leading: 1
      });
    }

    var righe = 0;

    var id_text = titolo_ele.node.id;

    var el = document.getElementById(id_text);
    var bbox = el.getBBox();
    righe = Math.round(bbox.height) + 10;
    var dim_txt = Math.round(bbox.width) + 10;

    if (vertical == "1") {

      if (width && height) {
        dim_txt += Math.round((height - (dim_txt * 2)) / 2) - 5;
      }

      $('#' + id_text).attr('transform', 'rotate(-90)translate(-' + dim_txt + ', -3)');

      // Questo se sto nel caso del caricamento dei dati e quindi centrare il testo
      //dim_txt += 10 ; 
    }

    var rect_width = rect_height = rect_x = rect_y = 0;
    if (width && height) {
      rect_width = width;
      rect_height = height;
    } else {

      if (vertical == "0") {
        console.log('Orizontal');
        rect_width = dim_txt;
        rect_height = righe;
      } else {
        console.log('Vertical');
        rect_width = righe;
        rect_height = dim_txt;
      }
    }
    rect_x = titolo_ele.x() - 7;
    rect_y = titolo_ele.y() - 4;

    var colore_att = "";
    if (!bg_color)
      colore_att = this.colore_area(colonna);
    else
      colore_att = bg_color;

    if (colonna == "12") {

      console.log('FLOAT TEXT', bbox);
      var height_txt_float = Math.round(bbox.height) + 10;
      var width_txt_float = Math.round(bbox.width) + 10;

      if (width_txt_float < rect_width) {
        var pos_txt_x = Math.round((rect_width - width_txt_float) / 2);
        var pos_txt_y = -3;
        if (height_txt_float < rect_height) {
          pos_txt_y = Math.round((rect_height - height_txt_float) / 2);
        }
        $('#' + id_text).attr('transform', 'translate( ' + pos_txt_x + ', ' + pos_txt_y + ')');
      }

      var rect = nested.rect(rect_width, rect_height).attr({'fill': colore_att});
    } else {
      var rect = nested.rect(rect_width, rect_height).attr({'fill': colore_att, 'stroke-width': svg_obj.spessore_bordo, 'stroke': svg_obj.colore_bordo});
    }

    rect.x(rect_x);
    rect.y(rect_y);

    // Questo serve per lo z index 
    rect.after(titolo_ele);

    nested.id(id_record);
    $('#' + id_record).attr('class', 'elemento');
    $('#' + id_record).attr('colonna', colonna);
    $('#' + id_record).attr('vertical', vertical);

    // Trascinamento
    nested.draggy();

    // Va fatto solo nel caso essitono link
    nested.on('dragmove', function (event) {
      svg_obj.crea_link();
    });

    // Va fatto solo nel caso essitono link
    nested.on('dragend', function (event) {
      svg_obj.salva_posizioni();
    });

    // Va fatto solo nel caso essitono link
    nested.on("dblclick", function (d) {
      svg_obj.double_click(this);
    });

    nested.on("mousedown", function (d) {
      var valore = d.which;
      var id_elemento = this.attr('id');
      if (valore == "3") {
        console.log('Right click:' + this.attr('id'));
        if (!$('#' + id_elemento).hasSvgClass('svg_select')) {
          $('#' + id_elemento).addSvgClass('svg_select');
        }
      } else
        console.log('click generico.');
    });

    // click, dblclick, mousedown, mouseup, mouseover, mouseout, 
    // mousemove, touchstart, touchmove, touchleave, touchend

    if (!width && !height) {
      // questa serve a risalvare le modifiche dopo aver trovato le dimenzioni
      $.ajax({
        url: '/c4d_rcd/ajax/update_element2',
        type: 'POST',
        cache: false,
        data: {
          'id_record': id_record,
          'width': rect_width,
          'height': rect_height,
          'x': s_x,
          'y': s_y
        },
        success: function (data_resp) {
          console.log('L\'elemento � stato modificato correttamente');
        },
        error: function () {
          console.log('La modifica dell\'elemento non � avvenuta correttamente.');
        }
      });
    }
  }
  ,
  // questo serve a creare i vari elementi e posizionarli sullo stage
  crea_elementi: function () {
    var contatore_colonna_1 = contatore_colonna_2 = 0;

    for (x = 0; x < this.json_data['elementi'].length; x++) {
      var singolo = this.json_data['elementi'][x];
      svg_obj.aggiungi_elemento_svg(singolo.id, singolo.titolo, singolo.descr, singolo.width, singolo.height, singolo.x, singolo.y, singolo.bg_color, singolo.colonna, singolo.vertical);
    }
    this.crea_link();
  }
  ,
  // Nel senso di linea, questo serve a calcolare le linee
  crea_link: function () {

    $(".linea").remove();
    arr_link = this.json_data['link'];

    console.log('**** Elenco link presenti: ', this.json_data['link']);


    for (x = 0; x < arr_link.length; x++) {

      var ele_1 = SVG.get(arr_link[x]['ele1']);
      var ele_2 = SVG.get(arr_link[x]['ele2']);

      var ele_1_id = arr_link[x]['ele1'];
      var ele_2_id = arr_link[x]['ele2'];

      var tipo_link = arr_link[x]['tipo'];


      var cat_1 = $('#' + arr_link[x]['ele1']).attr('colonna');
      var cat_2 = $('#' + arr_link[x]['ele2']).attr('colonna');

      var x1a = y1a = x1b = y1b = "";
      var x2a = y2a = x2b = y2b = "";

      if (ele_1 == null || ele_2 == null)
        continue;

      // Devo prendere il contenitore ma il quadrato contenuto
      quad_1 = ele_1.first();
      quad_2 = ele_2.first();

      x1a = ele_1.x();
      y1a = ele_1.y();

      x1b = x1a + quad_1.width();
      y1b = y1a + quad_1.height();

      x2a = ele_2.x();
      y2a = ele_2.y();

      x2b = x2a + quad_2.width();
      y2b = y2a + quad_2.height();

      line1_x = line1_y = line2_x = line2_y = 0;


      // Questo � il caso della linea verticale
      if (((x1b > (x2a)) && (x1b < (x2b))) || ((x1a < (x2b)) && (x1b > x2b)) || (x1a == x2a && x1b == x2b)) {

        line1_x = x1a + (quad_1.width() / 2);
        line2_x = x2a + (quad_2.width() / 2);

        if (y2a > (y1a + quad_1.height())) {
          line1_y = y1a + quad_1.height() - 3;
          line2_y = y2a - 3;
        } else if (y1a > (y2a + quad_2.height())) {
          line2_y = y2a + quad_2.height() - 3;
          line1_y = y1a - 3;
        }

      }
      // Caso della linea orizzontale
      else {

        line1_y = y1a + (quad_1.height() / 2);
        line2_y = y2a + (quad_2.height() / 2);

        // L'elemento 1 � a sinistra dell'elemento 2
        if (x1b < x2a) {
          // Tramite questa parte imposto i valori agli elementi
          if (typeof this.arr_elementi[ele_1] === 'object') {
            if (this.arr_elementi[ele_1_id].right.indexOf(ele_2_id) == -1) {
              this.arr_elementi[ele_1_id].right.push(ele_2_id);
            }
          } else {
            this.arr_elementi[ele_1_id] = {'right': [], 'left': []}
            this.arr_elementi[ele_1_id].right.push(ele_2_id);
          }

          if (typeof this.arr_elementi[ele_2] === 'object') {
            if (this.arr_elementi[ele_2_id].left.indexOf(ele_1_id) == -1) {
              this.arr_elementi[ele_2_id].left.push(ele_1_id);
            }
          } else {
            this.arr_elementi[ele_2_id] = {'right': [], 'left': []}
            this.arr_elementi[ele_2_id].left.push(ele_1_id);
          }


          line1_x = x1b;
          line2_x = x2a;
        }
        // L'elemento 1 � a destra dell'elemento 2
        else if (x1a > x2b) {

          // 
          if (typeof this.arr_elementi[ele_1_id] === 'object') {
            if (this.arr_elementi[ele_1_id].left.indexOf(ele_2_id) == -1) {
              this.arr_elementi[ele_1_id].left.push(ele_2_id);
            }
          } else {
            this.arr_elementi[ele_1_id] = {'right': [], 'left': []}
            this.arr_elementi[ele_1_id].left.push(ele_2_id);
          }

          if (typeof this.arr_elementi[ele_2] === 'object') {
            if (this.arr_elementi[ele_2_id].right.indexOf(ele_1_id) == -1) {
              this.arr_elementi[ele_2_id].right.push(ele_1_id);
            }
          } else {
            this.arr_elementi[ele_2_id] = {'right': [], 'left': []}
            this.arr_elementi[ele_2_id].right.push(ele_1_id);
          }

          line1_x = x1a;
          line2_x = x2b;
        }
      }

      line = draw.line((line1_x - 7), line1_y, (line2_x - 7), line2_y).stroke({width: 1}).back();
      $('#' + line.id()).attr('class', 'linea');

      // linea tratteggiata 
      if (tipo_link != "0") {
        $('#' + line.id()).attr('stroke-dasharray', '5,10,5');
      }
    }

    console.log('**** Elenco elementi presenti: ', this.arr_elementi);
  },

  double_click: function (oggetto) {

    var id_click = oggetto.node.attributes.id.value;
    var classe_presente = $("#" + id_click).hasSvgClass("svg_select");
    console.log('**** Funzione double_click.');
    console.log('**** ID click: ' + id_click);
    console.log('**** classe presente: ' + classe_presente);

    if (!classe_presente) {
      console.log('Aggiungi la classe');
      $("#" + id_click).addSvgClass("svg_select");
    } else {
      console.log('Togli la classe');
      $("#" + id_click).removeSvgClass("svg_select");
    }
    console.log(id_click);
  }
  ,
  zindex_top: function () {
    var numero = $('.svg_select').length;
    if (numero) {
      $('.svg_select').each(function (index, value) {
        id_sel = value.id;
        SVG.get(id_sel).front();
        $('#' + id_sel).removeSvgClass("svg_select");
      });
    }
  }
  ,
  elimina_elemento_db: function (id_elemento) {

    $.ajax({
      url: '/c4d_rcd/ajax/elimina_ele',
      type: 'POST',
      cache: false,
      data: {'id_elemento': id_elemento},
      dataType: 'json',
      success: function (json) {
        console.log('Cancellazioen avvenuta. ');
      }
      ,
      error: function () {
        console.log('Errore nella cancellazione');
      }
    });
  }
  ,
  // questa serve a cancellare un elemento
  elimina_elemento: function () {
    var numero = $('.svg_select').length;
    if (numero == 1) {

      // questo serve a cancellare l'elemento dall'svg
      var id_ele = $('.svg_select').attr('id');
      $('.svg_select').remove();
      svg_obj.elimina_elemento_db(id_ele);

      // questo serve a cancellare i link associati
      link = this.json_data['link'];
      var num_link = this.json_data['link'].length;
      var link_presente = 0;
      for (x = 0; x < num_link; x++) {
        if (link[x].ele1 == id_ele || link[x].ele2 == id_ele) {
          link_presente = 1;
          link.splice(x, 1);
        }
      }
      if (link_presente)
        this.json_data['link'] = link;
    } else {
      $('.svg_select').each(function (index, value) {
        $('#' + value.id).removeSvgClass("svg_select");
      });
    }
    svg_obj.salva_posizioni();
    svg_obj.crea_link();
  }
  ,
  // Questa serve a creare i link tra gli elementi
  aggiungi_link: function (tipo_link) {
    var numero = $('.svg_select').length;
    console.log("Numero elementi selezionati:" + numero);

    var ele_1 = ele_2 = vert_1 = vert_2 = "";
    $('.svg_select').each(function (index, value) {
      var id_sel = value.id;
      if (!ele_1)
        ele_1 = id_sel;
      else
        ele_2 = id_sel;

      var id_vert = $('#' + id_sel).attr('vertical');

      if (!vert_1)
        vert_1 = id_vert;
      else
        vert_2 = id_vert;
    });

    if (numero == 2 && (vert_1 == "0" && vert_1 == vert_2)) {

      console.log(ele_2 + " - " + ele_1)

      // Devo controllare se per caso esiste gi� un link di questo tipo
      var gia_linkato = 0;
      var link = this.json_data['link'];
      var num_link = this.json_data['link'].length;
      for (x = 0; x < num_link; x++) {

        if (((link[x].ele1 == ele_1) && (link[x].ele2 == ele_2)) || ((link[x].ele2 == ele_1) && (link[x].ele1 == ele_2))) {
          gia_linkato += 1;
          link.splice(x, 1);
        }
      }

      // Se sono collegati li rimuove altrimenti li collega
      if (gia_linkato == 0) {
        this.json_data['link'][num_link] = {'ele1': ele_1, 'ele2': ele_2, 'tipo': tipo_link};
      } else {
        this.json_data['link'] = link;
      }

      svg_obj.salva_posizioni();
      this.crea_link();

    }

    $(".svg_select").removeSvgClass("svg_select");
  }
  ,
  // questa serve ad evitare duplicati nei link
  link_unici: function () {

    var arr_new = [];
    var arr_link_len = this.json_data['link'].length;

    for (y = 0; y < arr_link_len; y++) {

      var ele1;
      var ele2;
      var main_ele1;
      var main_ele2;
      var trovato = false;
      for (x = 0; x < arr_new.length; x++) {
        ele1 = arr_new[x].ele1;
        ele2 = arr_new[x].ele2;
        main_ele1 = this.json_data['link'][y].ele1;
        main_ele2 = this.json_data['link'][y].ele2;
        if ((ele1 == main_ele1 && ele2 == main_ele2) || (ele1 == main_ele2 && ele2 == main_ele1)) {
          trovato = true;
        }
      }
      if (trovato == false)
        arr_new.push(this.json_data['link'][y]);
    }
    this.json_data['link'] = arr_new;
  }
  ,

  // Questa serve a recuperare tutte le posizioni degli elementi inseriti nella canvas
  json_posizioni: function () {

    this.link_unici();

    obj_main = {'elementi': [], 'link': this.json_data['link']};
    var contatore = 0;
    $('.elemento').each(function (index, value) {

      var bg_color = "";
      var valore_bg = $('#' + value.id + ' rect').attr('fill');
      if (svg_obj.colore_area_arr.indexOf(valore_bg) == -1) {
        bg_color = valore_bg;
      }

      obj_element = {
        'id': value.id,
        'x': SVG.get(value.id).x(),
        'y': SVG.get(value.id).y(),
        'colonna': $('#' + value.id).attr('colonna'),
        'width': $('#' + value.id + ' rect').attr('width'),
        'height': $('#' + value.id + ' rect').attr('height'),
        'bg_color': bg_color,
        'riga_1': '',
        'riga_2': '',
        'riga_3': '',
        'contatore': contatore
      };
      contatore += 1;
      obj_main.elementi.push(obj_element);
    });

    return obj_main;
  }
  ,
  // questa � la funzione salva posizioni
  salva_posizioni: _.debounce(function () {
    svg_obj.cambiamento_stato = false;
    $.ajax({
      url: '/c4d_rcd/ajax/save_positions',
      type: 'POST',
      cache: false,
      context: this,
      async: true,
      data: {
        'transform': $('#contenitore_main').attr('transform'),
        'area_select': $('#area_select').val(),
        'dati_posizione': svg_obj.json_posizioni(),
        'id_prj': $('#prj_id').val(),
      },
      success: function (resp) {

        svg_obj.aggiorna_scritta_zoom();

        // console.log('Salvataggio riuscito') ; 
        // svg_obj.cambia_prj($('#prj_id').val()) ;
      }
      ,
      error: function () {
        console.log('Errore ajax nel salvataggio delle posizioni.');
      }
    });
  }, 500),
  // questa � la funzione salva posizioni
  salva_posizioni_immediate: function () {
    svg_obj.cambiamento_stato = false;
    $.ajax({
      url: '/c4d_rcd/ajax/save_positions',
      type: 'POST',
      cache: false,
      context: this,
      async: true,
      data: {
        'transform': $('#contenitore_main').attr('transform'),
        'area_select': $('#area_select').val(),
        'dati_posizione': svg_obj.json_posizioni(),
        'id_prj': $('#prj_id').val(),
      },
      success: function (resp) {

        svg_obj.aggiorna_scritta_zoom();

        // console.log('Salvataggio riuscito') ; 
        // svg_obj.cambia_prj($('#prj_id').val()) ;
      }
      ,
      error: function () {
        console.log('Errore ajax nel salvataggio delle posizioni.');
      }
    });
  }
  ,
  aggiorna_scritta_zoom() {

    var matrix = decomposeMatrix();
    console.log(matrix);
    var valore_zoom = Math.round(matrix.scaleX * 100);

    $('#livello_zoom').html("Zoom : <b>" + valore_zoom + "%</b>");



  }
  ,
  // Questa serve scrivere l'elemento nel database, dopo averlo scritto riceve l'id elemento e 
  // lo passa a aggiungi elemento svg che lo posiziona sulla canvas
  // (bg_color, colonna_ele, id_prj, titolo, descr, vertical, link, hovering)
  aggiungi_elemento_db: function (bg_color, colonna_ele, id_prj, titolo, descr, vertical, link, hovering) {



    var riga_1 = riga_2 = riga_3 = "";
    // if(bg_color=="") bg_color="#ffffff";
    $.ajax({
      url: '/c4d_rcd/ajax/save_position',
      type: 'POST',
      cache: false,
      data: $('#form_inserisci_elemento').serializefiles(),
      dataType: 'json',
      processData: false,
      contentType: false,
      success: function (json) {
        var id_record = json.id;
        if (vertical == "1") {
          colonna_ele = json.colonna;
        }
        var s_x = svg_obj.right_click_pt.x;
        var s_y = svg_obj.right_click_pt.y;
        var width = 100;
        var height = 3 * 16;

        width = false;
        height = false;

        console.log('Aggiungi elemento_db', svg_obj.right_click_pt);

        console.log('Inserimento avvenuto');
        console.log('****** -> ' + bg_color + ', ' + colonna_ele + ', ' + riga_1 + ', ' + riga_2 + ', ' + riga_3 + ', ' + id_prj + ', ' + titolo + ', ' + descr + ', ' + vertical + ', ' + link);
        console.log('**** JSON RICEVUTO ****', json);
        svg_obj.aggiungi_elemento_svg(id_record, titolo, descr, width, height, s_x, s_y, bg_color, colonna_ele, vertical);

        svg_obj.cambia_prj($('#prj_id').val());
      },
      error: function () {
        // console.log('****** -> ' + bg_color + ', ' + colonna_ele + ', ' + riga_1 + ', ' + riga_2 + ', ' + riga_3 + ', ' + id_prj + ', ' + titolo + ', ' + descr + ', ' + vertical + ', ' + link);

        console.log('Errore nell\'inserimento dell\'elemento');
      }
    });
  }
  ,
  // questa � la funzioen che aggiorna le select dell epriority area
  aggiorna_priority_area: function (id_prj, elemento_select, valore_select) {
    if (!valore_select)
      valore_select = 0;
    console.log('Funzione -> aggiorna_priority_area');
    console.log('Valore select -> ' & valore_select);

    $.ajax({
      url: '/c4d_rcd/ajax/elenco_priority_area',
      data: {'id_prj': id_prj},
      cache: false,
      async: false,
      type: 'POST',
      dataType: 'json',
      success: function (json) {
        console.log(json);
        var len_prior = json.length;
        console.log('Elenco Priority area: ' + len_prior);

        // Questa � la parte che gestisce l'aggiunta degli elementi alla select area
        $('#' + elemento_select).html('');
        $('#' + elemento_select).append('<option value="0">Priority Areas</option>');

        svg_obj.colore_area_arr = [];
        svg_obj.colore_area_arr[12] = '#efefef';
        svg_obj.colore_area_arr[13] = '#fff';

        for (x = 0; x < len_prior; x++) {
          var id_area = json[x].id;
          var color = json[x].color;
          var descr = json[x].descr;
          var tipo = json[x].tipologia;
          if (tipo == "0") { // || tipo == "2"
            if (valore_select && id_area == valore_select) {
              $('#' + elemento_select).append('<option value="' + id_area + '" selected>' + descr + '</option>');
            } else {
              $('#' + elemento_select).append('<option value="' + id_area + '">' + descr + '</option>');
            }
          }

          svg_obj.colore_area_arr[id_area] = color;
        }
        svg_obj.colore_area_arr[100] = '#eeeeee';
      }
      ,
      error: function () {
        console.log('aggiorna_priority_area -> Errore nella chiamata ajax.');
      }

    });

  }
  ,
  mod_width: function (quanto) {
    svg_obj.cambiamento_stato = true;
    var numero = $('.svg_select').length;
    console.log("Numero elementi selezionati:" + numero);
    if (numero == 1) {
      // console.log('Un elemento selezionato');
      // var id_sel = $('.svg_select').attr('id');
      var width = parseInt($('.svg_select rect').attr('width'));
      var rect_height = parseInt($('.svg_select rect').attr('height'));
      var width_new = width + quanto;
      $('.svg_select rect').attr('width', width_new);

      var colonna = $('.svg_select').attr('colonna');
      var verticale = $('.svg_select').attr('vertical');

      if (colonna == "12" && verticale == "0") {
        var id_text = $('.svg_select text').attr('id');
        var x_att = SVG.get(id_text).x();
        var el = document.getElementById(id_text);
        var bbox = el.getBBox();
        var dim_txt = Math.round(bbox.width) + 10;
        var height_txt = Math.round(bbox.height) + 10;
        if (dim_txt < width_new) {
          var pos_txt_x = Math.round((width_new - dim_txt) / 2);

          var pos_txt_y = 0;
          if (height_txt < rect_height) {
            pos_txt_y = Math.round((rect_height - height_txt) / 2);
          }

          $('#' + id_text).attr('transform', 'translate( ' + pos_txt_x + ', ' + pos_txt_y + ')');
        }
      }

    }
  }

  ,
  // Questo serve a modificare la larghezza dell'elemento
  mod_height: function (quanto) {
    svg_obj.cambiamento_stato = true;
    var numero = $('.svg_select').length;
    console.log("Numero elementi selezionati:" + numero);
    if (numero == 1) {
      var height = parseInt($('.svg_select rect').attr('height'));
      var width = parseInt($('.svg_select rect').attr('width'));
      var width_new = width;
      var height_new = height + quanto;
      $('.svg_select rect').attr('height', (height_new));

      // Nel caso in cui sia verticale va centrato il testo rispetto all'elemento
      var verticale = $('.svg_select').attr('vertical');
      var colonna = $('.svg_select').attr('colonna');
      if (verticale == "1") {

        var id_text = $('.svg_select text').attr('id');
        var x_att = SVG.get(id_text).x();
        var pos_y = -1 * (quanto / 2) + x_att;

        console.log('x_att : ' + x_att + ' Quanto:' + quanto);
        SVG.get(id_text).x(pos_y);

      } else if (colonna == "12" && verticale == "0") {
        var id_text = $('.svg_select text').attr('id');
        var x_att = SVG.get(id_text).x();
        var el = document.getElementById(id_text);
        var bbox = el.getBBox();
        var dim_txt = Math.round(bbox.width) + 10;
        var height_txt = Math.round(bbox.height) + 10;
        if (dim_txt < width_new) {
          var pos_txt_x = Math.round((width_new - dim_txt) / 2);

          var pos_txt_y = 0;
          if (height_txt < height_new) {
            pos_txt_y = Math.round((height_new - height_txt) / 2);
          }

          $('#' + id_text).attr('transform', 'translate( ' + pos_txt_x + ', ' + pos_txt_y + ')');
        }
      }

    }
  }
  ,
  // Questa serve a popolare la form 
  popola_form_modifica: function (id_record) {

    // Questa � la parte che deve gestire la seguenza delle chimate ajax
    // cio� prima popola la select area, poi gli da l'id da usare 
    // quindi la funzione che gestisce il popolamento della select deve anche impostare l'id colonna ...
    $.ajax({
      url: '/c4d_rcd/ajax/dettaglio_elemento',
      cache: false,
      type: 'POST',
      dataType: 'json',
      data: {id_record: id_record},
      context: this,
      success: function (json) {

        console.log("Popola form", json);
        $('#colonna_ele').val(json.colonna);
        $('#id_ele').val(id_record);
        $('#titolo').val(json.titolo);
        $('#ordine_ele').val(json.ordine);
        console.log('**** COLONNA - > ', json.colonna);
        console.log('**** popola_form_modifica - > ', json);

        if (json.vertical == "0") {

          svg_obj.aggiorna_priority_area(json.id_prj, 'colonna_ele', json.colonna);
          $('#http_type').val(json.http_type);
          $('#link_ele').val(json.link);
          $('#descr').val(json.descr);
          $('#hovering').val(json.hovering);

          $('#bg_col').val(json.bg_color);
          $('.color-fill-icon').css('background-color', json.bg_color);

          var demo2 = $('#bg_color');
          demo2.colorpickerplus();
          demo2.on('changeColor', function (e, color) {
            if (color == null) {
              $('.color-fill-icon', $(this)).addClass('colorpicker-color');
            } else {
              $('.color-fill-icon', $(this)).removeClass('colorpicker-color');
              $('.color-fill-icon', $(this)).css('background-color', color);
            }

            $('#bg_col').val(color);
          });
        } else if (json.vertical == "1") {
          $('#hovering').val(json.hovering);

          $('#bg_col').val(json.bg_color);
          $('.color-fill-icon').css('background-color', json.bg_color);

          var demo2 = $('#bg_color');
          demo2.colorpickerplus();

          demo2.on('changeColor', function (e, color) {
            if (color == null) {
              $('.color-fill-icon', $(this)).addClass('colorpicker-color');
            } else {
              $('.color-fill-icon', $(this)).removeClass('colorpicker-color');
              $('.color-fill-icon', $(this)).css('background-color', color);
            }

            $('#bg_col').val(color);
          });
        }
      }
      ,
      error: function (bih) {
        console.log('Errore nel popolamento della form modifica');
      }

    });
  }
  ,
  // Questa serve a modificare l'elemetno sul database
  modifica_elemento_db: function () {
    $.ajax({
      url: '/c4d_rcd/ajax/update_element',
      type: 'POST',
      cache: false,
      async: false,
      data: $('#form_modifica_elemento').serializefiles(),
      processData: false,
      contentType: false,
      success: function (data_resp) {
        console.log('L\'elemento � stato modificato correttamente');
      },
      error: function () {
        console.log('La modifica dell\'elemento non � avvenuta correttamente.');
      }
    });

  }
  ,
  modifica_elemento: function () {
    var numero = $('.svg_select').length;
    var vertical = $('.svg_select').attr('vertical');
    var colonna_svg = $('.svg_select').attr('colonna');

    console.log("Numero elementi selezionati:" + numero);
    if (numero == 1) {

      var file_form = "form_modifica";
      if (vertical == "1")
        file_form = "form_modifica_vertical";
      else if (colonna_svg == "12")
        file_form = "form_modifica_float";
      else if (colonna_svg == "13")
        file_form = "form_modifica_impact";

      $.ajax({
        url: '/c4d_rcd/ajax_forms/' + file_form,
        type: 'POST',
        cache: false,
        dataType: 'html',
        context: this,
        success: function (data_html) {

          var str_titolo_txt = "Modify Result";
          if (vertical == "1") {
            str_titolo_txt = "Modify Priority Area";
          }

          BootstrapDialog.show({
            onshown: function (dialogRef) {
              var id_elemento = $('.svg_select').attr('id');
              svg_obj.popola_form_modifica(id_elemento);

            },
            nl2br: false,
            title: str_titolo_txt,
            message: data_html,
            cssClass: 'login-dialog',
            buttons: [{
                label: 'Save',
                cssClass: 'btn-primary',
                action: function (dialog) {

                  // PRIMA RECUPERO I DATI DELLA FORM

                  var id_ele = $('#id_ele').val();

                  var vertical = $('#vertical').val();
                  var titolo = $('#titolo').val();
                  if (!titolo)
                    titolo = "";

                  var colonna_ele = $('#colonna_ele').val();
                  var colore_att = svg_obj.colore_area(colonna_ele);

                  console.log('******-> controlloo colore ->', colonna_ele, " - ", colore_att);

                  var colore_form = $('#bg_col').val();
                  if (colore_form)
                    colore_att = colore_form;

                  if (vertical == "0") {
                    var descr = $('#descr').val();
                    if (!descr)
                      descr = " ";
                    var arr_descr = descr.split("\n");
                  }

                  var errore_validazione = "";


                  // Prima deve scrivere le modifiche sul database, poi aggiorno il quadrato posizionato sulla canvas
                  // Questo � il test per la completezza dei campi

                  // if(titolo==""){
                  // 	errore_validazione = "Attenzione. Il titolo risulta essere vuoto."; 
                  // }
                  //else 
                  if (colonna_ele == "0") {
                    errore_validazione = "Attenzione. Bisogna selezionare la priority area.";
                  }

                  if (errore_validazione != "") {
                    alert(errore_validazione);
                  } else {
                    svg_obj.modifica_elemento_db();
                    dialog.close();
                    svg_obj.cambia_prj($('#prj_id').val());
                  }
                }
              }]
          });
        }
      });

    } else {
      console.log('Non pu� essere selezionato pi� di un elemento');
    }
  }
  ,
  modifica_db: function () {
    $.ajax({
      data: $('#form_modifica_elemrnto').serialize(),
      url: '',
      type: 'POST',
      cache: false,
      success: function (resp) {

      }
    });
  }
  ,
  // Questa serve ad aggiungere l'elemento vertical all'svg
  aggiungi_vertical: function () {
    $.ajax({
      url: '/c4d_rcd/ajax_forms/form_inserisci_vertical',
      type: 'POST',
      cache: false,
      dataType: 'html',
      context: this,
      success: function (data_html) {
        BootstrapDialog.show({
          nl2br: false,
          title: 'Add Priotity Area',
          onshown: function (dialogRef) {
            var demo2 = $('#bg_color');
            demo2.colorpickerplus();
            demo2.on('changeColor', function (e, color) {
              if (color == null) {
                $('.color-fill-icon', $(this)).addClass('colorpicker-color');
              } else {
                $('.color-fill-icon', $(this)).removeClass('colorpicker-color');
                $('.color-fill-icon', $(this)).css('background-color', color);
              }

              $('#bg_col').val(color);
            });
          },
          message: data_html,
          cssClass: 'login-dialog',
          buttons: [{
              label: 'Save',
              cssClass: 'btn-primary',
              action: function (dialog) {

                var colonna_ele = $('#colonna_ele').val();
                var id_prj = $('#prj_id').val();
                var titolo = $('#titolo').val();
                var hovering = $('#hovering').val();
                var bg_color = $('#bg_col').val();

                // if(!bg_color) bg_color = "#ffcc00";

                var vertical = 1;
                var link = descr = "";

                $('#id_prj').val(id_prj);

                if (titolo == "") {
                  alert('Attenzione bisogna prima indicare il titolo.');
                } else if (!bg_color) {

                  alert('Attenzione bisogna prima impostare il colore.');
                } else {
                  svg_obj.aggiungi_elemento_db(bg_color, colonna_ele, id_prj, titolo, descr, vertical, link, hovering); // l'ultimo valore � l'hovering
                  dialog.close();
                }
              }
            }]
        });
      }
    });
  }
  ,
  aggiungi_scritta_float: function () {
    $.ajax({
      url: '/c4d_rcd/ajax_forms/form_inserisci_float',
      type: 'POST',
      cache: false,
      dataType: 'html',
      context: this,
      success: function (data_html) {
        BootstrapDialog.show({
          title: 'Add Floating Text',
          onshown: function (dialogRef) {
          },
          nl2br: false,
          message: data_html,
          cssClass: 'login-dialog',
          buttons: [{
              label: 'Save',
              cssClass: 'btn-primary',
              action: function (dialog) {

                var colonna_ele = $('#colonna_ele').val();
                var titolo = $('#titolo').val();

                var link = bg_color = descr = "";
                var id_prj = $('#prj_id').val();
                $('#id_prj').val(id_prj);
                svg_obj.aggiungi_elemento_db(bg_color, colonna_ele, id_prj, titolo, descr, 0, link, ''); // l'ultimo valore � l'hovering

                dialog.close();
              }
            }]
        });
      }
    });
  }
  ,
  // questa � la paret che aggiunge l'impact
  aggiungi_impact: function () {
    $.ajax({
      url: '/c4d_rcd/ajax_forms/form_inserisci_impact',
      type: 'POST',
      cache: false,
      dataType: 'html',
      context: this,
      success: function (data_html) {
        BootstrapDialog.show({
          title: 'Add Impact',
          onshown: function (dialogRef) {
          },
          nl2br: false,
          message: data_html,
          cssClass: 'login-dialog',
          buttons: [{
              label: 'Save',
              cssClass: 'btn-primary',
              action: function (dialog) {

                var colonna_ele = $('#colonna_ele').val();
                var titolo = $('#titolo').val();
                var descr = $('#descr').val();
                var hovering = $('#hovering').val();
                var id_prj = $('#prj_id').val();
                var link = bg_color = "";

                $('#id_prj').val(id_prj);

                // L'ultimo valore � l'hovering 
                svg_obj.aggiungi_elemento_db(bg_color, colonna_ele, id_prj, titolo, descr, 0, link, hovering);

                dialog.close();
              }
            }]
        });
      }
    });
  }
  ,
  aggiungi_elemento: function () {
    $.ajax({
      url: '/c4d_rcd/ajax_forms/form_inserisci',
      type: 'POST',
      cache: false,
      dataType: 'html',
      context: this,
      success: function (data_html) {
        BootstrapDialog.show({
          nl2br: false,
          title: 'Add Result',
          onshown: function (dialogRef) {
            var id_prj = $('#prj_id').val();
            svg_obj.aggiorna_priority_area(id_prj, 'colonna_ele');

            var demo2 = $('#bg_color');
            demo2.colorpickerplus();
            demo2.on('changeColor', function (e, color) {
              if (color == null) {
                $('.color-fill-icon', $(this)).addClass('colorpicker-color');
              } else {
                $('.color-fill-icon', $(this)).removeClass('colorpicker-color');
                $('.color-fill-icon', $(this)).css('background-color', color);
              }
              $('#bg_col').val(color);
            });
          },
          message: data_html,
          cssClass: 'login-dialog',
          buttons: [{
              label: 'Save Result',
              cssClass: 'btn-primary',
              action: function (dialog) {

                var colonna_ele = $('#colonna_ele').val();
                var titolo = $('#titolo').val();
                var descr = $('#descr').val();

                var link = $('#link_ele').val();
                var bg_color = $('#bg_col').val();
                var id_prj = $('#prj_id').val();
                var hovering = $('#hovering').val();

                $('#id_prj').val(id_prj);

                console.log('->>> Verifica form', colonna_ele, titolo, descr, link, bg_color, id_prj, hovering);

                // console.log('INVIO DB' , bg_color, colonna_ele, id_prj, titolo, descr, 0, link, hovering);
                if (colonna_ele == "0") {
                  alert('Attenzione bisogna selezionare la priority area.');
                } else {
                  svg_obj.aggiungi_elemento_db(bg_color, colonna_ele, id_prj, titolo, descr, 0, link, hovering);
                  dialog.close();
                }
              }
            }]
        });
      }
    });
  }


};

svg_obj.init();



/*
 
 // Questo � il pezzo di testo che gestisce 
 // l'hover con il cambio di colore
 
 var draw = SVG('drawing').size(300, 130)
 var circle = draw.circle(50).fill('#fff')
 
 var mask = draw.mask()
 mask.add(circle.center(35, 35))
 mask.add(circle.clone().center(70, 70).size(70).fill('#ccc'))
 mask.add(circle.clone().center(90, 30).size(30).fill('#999'))
 mask.add(circle.clone().center(105, 115).size(50).fill('#333'))
 
 var rect = draw.rect(100, 100).move(20, 20).fill('#f06')
 rect.maskWith(mask)
 
 rect.on('mouseover', function() {
 this.animate(300, '<>').fill('#0f9')
 })
 rect.on('mouseout', function() {
 this.animate(300, '<>').fill('#f06')
 })
 
 
 */