console.log('Ciao mondo');

function sleepFor(sleepDuration) {
  var now = new Date().getTime();
  while (new Date().getTime() < now + sleepDuration) { /* do nothing */
  }
}

// Istruzioni menu contestuale: 
// https://github.com/dgoguerra/bootstrap-menu

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

// 99vh
var draw_main = SVG('drawing');
draw_main.id('contenitore_main1');

var draw = draw_main.group();
draw.id('contenitore_main');

// ****** Terzo gruppo con i comandi 
var comandi_group = draw_main.group();
comandi_group.id('contenitore_comandi');


arr = [];
arr[0] = 0.25;
arr[1] = 1.50;
// zoom_att = draw.panZoom({'zoom' : arr , 'zoomSpeed ' : 0});
zoom_att = draw.panZoom({'zoom': arr, 'zoomSpeed ': 0});
// console.log('**** Inizializzazione pan zoom ****');
// console.log(zoom_att);

// var scalex = 0.25 ;



var image_plus = comandi_group.image(modulePath + 'front/images/plus.jpg', 50, 25);
image_plus.x('91%');
image_plus.y(10);

var image_minus = comandi_group.image(modulePath + 'front/images/minus.jpg', 50, 25);
image_minus.x('94%');
image_minus.y(10);



image_minus.on('click', function (d) {
  var scalex = decomposeMatrix().scaleX;
  console.log('Click minus');
  if (scalex > 0.02)
    scalex -= 0.02;
  // console.log( zoom_att);
  zoom_att.zoom(scalex)

});


image_plus.on('click', function (d) {
  var scalex = decomposeMatrix().scaleX;
  console.log('Click plus');
  // if(zoom_att.transform!==undefined)console.log('Zoom attuale: ' + zoom_att.transform.scaleY);
  scalex += 0.02;
  // console.log( zoom_att);
  zoom_att.zoom(scalex)
});

console.log('Larghezza svg: ' + draw_main.width());




// rect = comandi_nested.rect('10%', '5%').attr({'fill': '#ffcc00'}); 


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


function sleep(time) {
  // return new Promise((resolve) => setTimeout(resolve, time));

  var promise = new Promise(function (resolve) {
    setTimeout(function () {
      resolve("result");
    }, time);
  });

  return promise;
}




var draw_container1 = document.getElementById("contenitore_main1");
var draw_container = document.getElementById("contenitore_main");

var svg_obj = {
  last_hover: 0,
  right_click_pt: 0,
  cambiamento_stato: false,
  arr_linked: [],
  spessore_bordo: '1px',
  colore_border: 'rgb(0,0,0)',
  colore_area_arr: [],
  color_specific_element_arr: [],
  doppio_click: 0,
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

    // this.riempi_array_colori() ; 
    // this.carica_progetti(); 
    var id_prj = $('#prj_id').val();
    console.log('Init', id_prj);
    this.cambia_prj($('#prj_id').val());
    setInterval(svg_obj.aggiorna_stato, 3000);

    // $('.elemento').removeClass("svg_select");

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

      $('.svg_select').removeClass("svg_select");


      // questo va fatto al contrario
      // in pratica cerco tutti quelli che non hanno svg
      $.each(svg_obj.arr_linked, function (index, value) {
        console.log(value);
        $('#' + value).addClass("svg_link");
      });

      $('.elemento').each(function (index) {
        if (!$(this).hasClass("svg_link"))
          $(this).addClass("svg_select");
      });
      $('.svg_link').removeClass("svg_select");
    }
  }
  ,
  // Questa serva  trovare un link
  trova_link: function (id_elemento, tipologia) {
    console.log('trova link -> id_elemento', id_elemento);
    id_elemento = parseInt(id_elemento);

    if (tipologia == "right") {
      if (typeof svg_obj.arr_elementi[id_elemento] !== 'undefined') {
        $.each(svg_obj.arr_elementi[id_elemento].right, function (index, value) {
          if (value) {
            svg_obj.arr_linked.push(value);
            svg_obj.trova_link(value, tipologia);
          }
        });
      }
    } else {
      if (typeof svg_obj.arr_elementi[id_elemento] !== 'undefined') {
        $.each(svg_obj.arr_elementi[id_elemento].left, function (index, value) {
          if (value) {
            svg_obj.arr_linked.push(value);
            svg_obj.trova_link(value, tipologia);
          }
        });
      }
    }
  }
  ,
  // Questa serev acambiare il projetto
  cambia_prj: function (id_prj) {
    $('#contenitore_main').html('');
    this.json_data = [];
    this.arr_elementi = [];
    this.arr_righe = [];
    this.arr_linked = [];

    // *** EX PAN ZOOM

    console.log('Function -> cambia_prj -> Gestione della select cambio prj.');

    if (id_prj != "0") {
      this.aggiorna_priority_area(id_prj, 'area_select');
      this.get_json(id_prj);

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
  // Questa va modificata e va aggiunto lo zoom ed il pan
  get_json: function (id_prj) {
    $.ajax({
      cache: false,
      type: 'POST',
      context: this,
      async: false,
      url: basePath + 'c4d_rcd/ajax/load_positions',
      data: {area_select: $('#area_select').val(), 'id_prj': id_prj},
      dataType: 'json',
      success: function (json) {
        console.log('**** JSON ELEMENTI ', json);
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

      $('#' + id_text).attr('transform', 'rotate(-90) translate(-' + dim_txt + ', -3)');
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


    // nested.draggy() ; 

    if (vertical == "1") {
      nested.on("click", function (d) {
        console.log('Vertical click', id_record, colonna);
        // Devo fare un foreach e mettere su tutti quelli che non sono di quella categoria un css di minchia

        $('.elemento').removeClass("svg_select");

        // non mi ricordo se serve a qualcosa....
        $('.elemento').each(function (index) {
          var colo = $(this).attr('colonna');
          console.log(colo);
          if (colo != colonna) {
            $(this).addClass("svg_select");
          }
        });

      });
    } else if (colonna != "12") {

      nested.on('dblclick', function () {
        console.log('**** Inizio doppio click');

        console.log('**** Oggetti linkati: ', svg_obj.arr_linked);
        console.log('**** Numero oggetti linkati: ', svg_obj.arr_linked.length);
        console.log('**** Id selezionato: ' + id_record);
        svg_obj.doppio_click = 1;

        // nel caso in cui non esistono oggetti selezionati
        if (svg_obj.arr_linked.length < 1) {

          for (x = 0; x < svg_obj.json_data.elementi.length; x++) {
            var id_att = svg_obj.json_data.elementi[x].id;
            if (id_att == id_record) {

              var a = document.createElement('a');
              a.href = basePath + 'results-indicators/' + $('#prj_id').val() + '/' + id_record + '/all';
              //a.href= 'http://capacity4dev-old.local/web1/indicator_list/' +  $('#prj_id').val() + "/" + id_record ; 
              a.target = '_blank';
              a.className = "link_creato";
              document.body.appendChild(a);
              a.click();
              // console.log('Link select -> ', link_start);
              console.log('Invio link');
              // tolgo il link
              $('.link_creato').remove();
              // tolgo tutti i link opachi
              $('.svg_select').removeClass("svg_select");

            }
          }
        } else {
          // console.log(' � stata selezionata una catena di elementi')
          // esempio di link
          // http://localhost:8080/capacity4dev/web1/indicator_list/16/7911-7916-7921
          var codice = "";
          var str = "";
          var len_arr = svg_obj.arr_linked.length;
          // console.log("Lunghezza array -> " , len_arr)

          // questa deve funzionare solo se l'elemento cliccato � nella catena dei selezionati



          var nella_catena = false;
          for (x = 0; x < len_arr; x++) {
            if (svg_obj.arr_linked[x] == id_record)
              nella_catena = true;
            str = svg_obj.arr_linked[x] + "+";
            codice += str;
          }

          if (nella_catena) {

            codice = codice.substr(0, (codice.length - 1));

            var a = document.createElement('a');
            //a.href= 'http://capacity4dev-old.local/web1/indicator_list/' +  $('#prj_id').val() + "/" + codice + "/" + id_record ; 

            if (codice.length < 1) {
              codice = 'all';
            }
            a.href = basePath + 'results-indicators/' + $('#prj_id').val() + '/' + id_record + '/' + codice;

            a.target = '_blank';
            a.className = "link_creato";
            document.body.appendChild(a);
            a.click();
            $('.link_creato').remove();
            // ma senza togliere  la riga selezionata
          }
        }

      });


      nested.on("click", function (d) {
        svg_obj.doppio_click = 0;
        sleep(300).then(function (result) {
          if (!svg_obj.doppio_click) {

            svg_obj.arr_linked = [];
            var id_select = id_record;
            svg_obj.arr_linked.push(id_select);
            svg_obj.trova_link(id_select, 'right');
            svg_obj.trova_link(id_select, 'left');

            $('.svg_select').removeClass("svg_select");

            // questo va fatto al contrario
            // in pratica cerco tutti quelli che non hanno svg
            $.each(svg_obj.arr_linked, function (index, value) {
              console.log(value);
              $('#' + value).addClass("svg_link");
            });

            $('.elemento').each(function (index) {
              if (!$(this).hasClass("svg_link"))
                $(this).addClass("svg_select");
            });
            $('.svg_link').removeClass("svg_link");
          }
        });
      });



    }

    $('.elemento').hover(
            // Caso di hover in 
                    function () {



                      var id_att = $(this).attr('id');
                      var colonna_att = $(this).attr('colonna');
                      var vertical_att = $(this).attr('vertical');
                      if (id_att != svg_obj.last_hover && colonna_att != "12") {
                        svg_obj.last_hover = id_att;
                        var d = new Date();
                        var t = d.getTime();
                        // console.log('Hover On.', t );
                        // a seconda che � vertical o no, fa una cosa diversa

                        var hover_data = svg_obj.hovering_from_id(id_att);
                        // var x_pos = Math.round(hover_data.x) - 7 ;
                        var x_pos = Math.round(hover_data.x) + Math.round(hover_data.width) + 10;
                        var y_pos = Math.round(hover_data.y) + (Math.round(hover_data.height) / 2) + 10;
                        var larghezza_rettangolo = hover_data.width;
                        var altezza_rettangolo = 100;
                        var txt_hovering = hover_data.txt;
                        $('#hovering').remove();

                        if (txt_hovering != null && txt_hovering != "") {

                          if (vertical_att == '1') {
                            x_pos = Math.round(hover_data.x) + Math.round(hover_data.width) + 10;
                            y_pos = Math.round(hover_data.y) - 3;
                            larghezza_rettangolo = 100;
                            altezza_rettangolo = hover_data.height;
                          }


                          var nested = draw.nested();
                          // console.log( hover_data, 'Y pos' ,y_pos);
                          nested.x(x_pos);
                          nested.y(y_pos);
                          nested.id('hovering');
                          var rect = nested.rect(larghezza_rettangolo, altezza_rettangolo).attr({'fill': '#ffffe1', 'stroke': '#9eafb6'});
                          rect.x(0);
                          // rect.y(0); 

                          //if(vertical_att=='1'){
                          rect.y(-4);
                          // }

                          // inserimento testo dell'hovering
                          var titolo_ele = nested.text(function (add) {

                            var arr_descr = txt_hovering.split("\n");
                            for (z = 0; z < arr_descr.length; z++) {
                              if (arr_descr[z] != "") {
                                add.tspan(arr_descr[z]).newLine();
                              }
                            }
                          }).attr({'fill': '#444'}); // #8f8b88
                          titolo_ele.x(4);
                          titolo_ele.y(8);
                          titolo_ele.font({
                            family: 'tahoma',
                            size: 14,
                            leading: 1
                          });

                          var id_text = titolo_ele.node.id;

                          var el = document.getElementById(id_text);
                          var bbox = el.getBBox();
                          var alt_txt = Math.round(bbox.height) + 15;
                          var larg_txt = Math.round(bbox.width) + 10;

                          // console.log('Altezza_txt' , alt_txt, 'Larghezza_txt', larg_txt);

                          if (larghezza_rettangolo < larg_txt)
                            rect.width(larg_txt);
                          rect.height(alt_txt);

                          // sposto tutto il pezzo al centro del vertical
                          if (vertical_att == "1") {
                            var y_add = Math.round((altezza_rettangolo - alt_txt) / 2);
                            nested.y(y_pos + y_add);
                          }


                          // questo dovrebbe essere il pezzo in cui aggiungo il testo dell'hovering


                        }

                        // console.log('Hover -> ', hover_data); 
                        // console.log('Hover In', '  | ' , 'Id attuale:' , id_att , ' | Colonna:' , colonna_att, ' | Vertical:' , vertical_att) ; 
                      }
                    },
                    // Caso di hover out 
                            function () {
                              $('#hovering').remove();
                              var id_att = $(this).attr('id');
                              var colonna_att = $(this).attr('colonna');
                              var vertical_att = $(this).attr('vertical');
                              if (svg_obj.last_hover != 0 && colonna_att != "12") {
                                // console.log('Hover Off.');
                                svg_obj.last_hover = 0;
                                // var hover_txt = svg_obj.hovering_from_id(id_att);
                                // console.log('Hover -> ', hover_txt); 
                                // console.log('Hover Out', ' | ' , 'Id attuale:' , id_att , ' | Colonna:' , colonna_att, ' | Vertical:' ,  vertical_att) ; 
                              }
                            }
                    );


                    // HOVERING
                    // http://www.petercollingridge.co.uk/interactive-svg-components/tooltip

                    // EVENTI 
                    // click, dblclick, mousedown, mouseup, mouseover, mouseout, 
                    // mousemove, touchstart, touchmove, touchleave, touchend

                    if (!width && !height) {
                      // questa serve a risalvare le modifiche dopo aver trovato le dimenzioni
                      $.ajax({
                        url: basePath + 'c4d_rcd/ajax//update_element2',
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
          // questa dato un id cerca di recuperare la stringa hovering
          hovering_from_id: function (id_elemento) {
            for (x = 0; x < this.json_data['elementi'].length; x++) {
              var singolo = this.json_data['elementi'][x];
              var id_sing = singolo.id;
              if (id_sing == id_elemento) {

                // console.log('*** Function hovering_from_id', id_sing, 'Oggetto singolo-> ',  singolo) ; 

                var txt = singolo.hovering;
                var h_x = singolo.x;
                var h_y = singolo.y;
                var h_w = singolo.width;
                var h_h = singolo.height;
                return {x: h_x, y: h_y, width: h_w, height: h_h, txt: txt};
              }
            }
            return {x: null, y: null, width: null, height: null, txt: null};
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
                      if (tipo_link != "1")
                        this.arr_elementi[ele_1_id].right.push(ele_2_id);
                    }
                  } else {
                    this.arr_elementi[ele_1_id] = {'right': [], 'left': []}
                    if (tipo_link != "1")
                      this.arr_elementi[ele_1_id].right.push(ele_2_id);
                  }

                  if (typeof this.arr_elementi[ele_2] === 'object') {
                    if (this.arr_elementi[ele_2_id].left.indexOf(ele_1_id) == -1) {
                      if (tipo_link != "1")
                        this.arr_elementi[ele_2_id].left.push(ele_1_id);
                    }
                  } else {
                    this.arr_elementi[ele_2_id] = {'right': [], 'left': []}
                    if (tipo_link != "1")
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
                      if (tipo_link != "1")
                        this.arr_elementi[ele_1_id].left.push(ele_2_id);
                    }
                  } else {
                    this.arr_elementi[ele_1_id] = {'right': [], 'left': []}
                    if (tipo_link != "1")
                      this.arr_elementi[ele_1_id].left.push(ele_2_id);
                  }

                  if (typeof this.arr_elementi[ele_2] === 'object') {
                    if (this.arr_elementi[ele_2_id].right.indexOf(ele_1_id) == -1) {
                      if (tipo_link != "1")
                        this.arr_elementi[ele_2_id].right.push(ele_1_id);
                    }
                  } else {
                    this.arr_elementi[ele_2_id] = {'right': [], 'left': []}
                    if (tipo_link != "1")
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
          }
          ,
          double_click: function (oggetto) {

            var id_click = oggetto.node.attributes.id.value;
            var classe_presente = $("#" + id_click).hasClass("svg_select");
            console.log('**** Funzione double_click.');
            console.log('**** ID click: ' + id_click);
            console.log('**** classe presente: ' + classe_presente);

            if (!classe_presente) {
              console.log('Aggiungi la classe');
              $("#" + id_click).addClass("svg_select");
            } else {
              console.log('Togli la classe');
              $("#" + id_click).removeClass("svg_select");
            }
            console.log(id_click);
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
          salva_posizioni: function () {
            $('.elemento').removeClass("svg_select");
            svg_obj.arr_linked = [];
          }
          ,
          // questa � la funzioen che aggiorna le select delle priority area
          aggiorna_priority_area: function (id_prj, elemento_select, valore_select) {
            if (!valore_select)
              valore_select = 0;
            console.log('Funzione -> aggiorna_priority_area');
            console.log('Valore select -> ' & valore_select);

            $.ajax({
              url: basePath + 'c4d_rcd/ajax/elenco_priority_area',
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
              error: function (resp) {
                console.log(resp);
                console.log('aggiorna_priority_area -> Errore nella chiamata ajax.');
              }

            });

          }
          ,
          aggiungi_elemento: function () {
            $.ajax({
              url: basePath + 'c4d_rcd/ajax/form_inserisci',
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


                        // console.log('INVIO DB' , bg_color, colonna_ele, id_prj, titolo, descr, 0, link, hovering);

                        if (colonna_ele == "0" || titolo == "") {
                          alert('Attenzione bisogna inserire il titolo e selezionare la priority area.');
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

