(function(factory){
    "use strict";
    if (typeof define === 'function' && define.amd) {
        define(['jquery','bootstrap-colorpicker'], factory);
    } else if (window.jQuery && !window.jQuery.fn.colorpickerplus) {
        factory(window.jQuery);
    }	
}(function($){
	var panelColors = ["#ffc0b6", // rosa tenue 
	"#ff4040", // Salmone scuro 
	"#ffefce", // Vaniglia 
	"#ffc281", // crema 
	"#ff8141", // pesca 
	"#ffffc2", // giallo paglierino 
	"#ffff00", // giallo 
	"#ffe118", // senape 
	"#e1e100", // giallo acido 
	"#c2ff91", // sedano
	"#e0ffff", // azzurro ghiaccio
	"#c0e1ff", // fiordaliso chiaro
	"#e0e0ff", // lilla nebbia
	"#ff9fff" // orchidea rosato
	];
    var storage = window.localStorage;
    var customColors = [];
    if(!!storage) {
        if(!storage.getItem("colorpickerplus_custom_colors")) {
            storage.setItem("colorpickerplus_custom_colors",customColors.join('$'));
        }
        customColors = storage.getItem("colorpickerplus_custom_colors").split('$');
    }
	var ROWS = 2;
	var CELLS = 10;
    var createColorCell = function(color, cell) {
        if(!cell) {
          cell = $('<div class="colorcell"></div>');
		}
        if(!!color) {
          cell.data('color', color);
          cell.css('background-color', color);
        } else {
          cell.addClass('colorpicker-color');//alpha
        }
        return cell;        
    };
    var ColorpickerEmbed = function(element) {
        
		var container = $(element);
        var customRows = Math.max(Math.ceil(customColors.length/CELLS), 1);
        var row = null;
		
        for(i=0;i<ROWS;i++) {
            row = null;
            if(i<ROWS-2) {
                row = $('<div class="colorpickerplus-colors-row"></div>');
            } else {
			  if(i===ROWS-2) {
			    $('<div class="colorpickerplus-custom-colors"></div>').appendTo(container);
			  }
                row = $('<div class="colorpickerplus-colors-row"></div>');
			}
			
            for(var jj=0;jj<CELLS;jj++) {
                var cc = panelColors[i*CELLS+jj];
				// console.log('Colore select:' , cc);
				if(typeof cc == 'undefined'){
					cell = $('<div class="nonecell"></div>');
					cell.appendTo(row);
				}
				else {
					createColorCell(cc).appendTo(row);
				}
            }
            row.appendTo(container);
        }
        
		var inputGrp = $('<div class="input-group input-group-sm"><input type="text" class="form-control"/><span class="input-group-btn"><button class="btn btn-default" type="button" title="Custom Color">C</button></span></div>');
		// var inputGrp = $('<div class="input-group input-group-sm"></div>');
        var colorInput = $('input', inputGrp);
        inputGrp.appendTo(container);
		// console.log('ciao ' , $.proxy(this.select, this));
        container.on('click.colorpickerplus-container', '.colorcell', $.proxy(this.select, this));
        inputGrp.on('click.colorpickerplus-container', 'button', $.proxy(this.custom, this));
        colorInput.on('changeColor.colorpickerplus-container', $.proxy(this.change, this));
		container.on('click', $.proxy(this.stopPropagation, this));
        colorInput.colorpicker();
        //colorInput.data('colorpicker').picker.on('click touchstart', $.proxy(this.stopPropagation, this));
        this.element = element;
        this.colorInput = colorInput[0]; 
		
    };
    ColorpickerEmbed.prototype = {
        constructor: ColorpickerEmbed,
        custom: function() {
			var $element = $(this.element);
            var color = $(this.colorInput).val();
            customColors[customColors.length] = color;
            var cells = $('.nonecell', $element);
            var cell = createColorCell(color, cells.first());
            cell.removeClass('nonecell');
            cell.addClass('colorcell');
            storage.setItem("colorpickerplus_custom_colors",customColors.join('$'));
        },
        select: function(e) {
			var $element = $(this.element);
            var c = $(e.target).data('color');
			// questo è il colore seleionato, in realtà si dovrebbe chiudere così, 
			// senza far fare il giro di peppe, però ci teniamo lo steso sta cazzata
			// console.log(c);
            if(c==null) {
              $element.trigger('changeColor',[c]);
            } else {
			  var colorInput = $(this.colorInput);
              colorInput.val(c);
              colorInput.colorpicker('setValue', c);
              this.update(c);
            }
            $element.trigger('select',[c]);
            $(this.colorInput).colorpicker('hide');
        },
        change: function(e) {
			var $element = $(this.element);
            e.stopPropagation();
            $element.trigger('changeColor',[e.color.toHex()]);
        },
        update: function(color) {
			var $element = $(this.element);
            var cells = $('.colorcell', $element);
            cells.removeClass('selected');
            if(color!=null) {
			  var colorInput = $(this.colorInput);
              colorInput.val(color);
            }
            cells.each(function(){
                var c = $(this).data('color');
                if(color!=null&&c===color.toUpperCase()) {
                    $(this).addClass('selected');
                    return false;
                }
            });
        },
        stopPropagation:function(e) {
            // if (!e.pageX && !e.pageY && e.originalEvent) {
            //     e.pageX = e.originalEvent.touches[0].pageX;
            //     e.pageY = e.originalEvent.touches[0].pageY;
            // }
			var target = $(e.target);
            if(!target.is('.colorcell')) {			 
              e.stopPropagation();
              //e.preventDefault();
			}
        }
    };
    $.colorpickerembed = ColorpickerEmbed;

    $.fn.colorpickerembed = function(option) {
        var pickerArgs = arguments;

        return this.each(function() {
            var $this = $(this),
            inst = $this.data('colorpickerembed'),
            options = ((typeof option === 'object') ? option : {});
            if ((!inst) && (typeof option !== 'string')) {
                $this.data('colorpickerembed', new ColorpickerEmbed(this, options));
            } else {
                if (typeof option === 'string') {
                    inst[option].apply(inst, Array.prototype.slice.call(pickerArgs, 1));
                }
            }
        });
    };
    $.fn.colorpickerembed.constructor = ColorpickerEmbed;
    //singleton
	var colorpickerplus = $('.colorpickerplus');
	if(colorpickerplus.length<=0) {
      colorpickerplus = $('<div class="colorpickerplus"></div>');
	  colorpickerplus.appendTo($('body'));
	  //console.log('append singleton to body');
	}
    var _container = $('<div class="colorpickerplus-container"></div>').appendTo(colorpickerplus);
    _container.colorpickerembed();
    var currPicker = null;
    _container.on('changeColor', function(e, val){
	  //console.log('color:'+val);
        if(!!currPicker) {		  
	  //console.log('color:'+val);
            currPicker.setValue(val);
        }
    });
    _container.on('select', function(){
        if(!!currPicker) {
            // currPicker.setValue(c);
            hide();
        }
    });
    //var embed = _container.data('colorpickerembed');
	/*
    colorpickerplus.on('mouseup.colorpickerplus', function(e) {
		var target = $(e.target);
        if(!target.is('input')) {
			e.stopPropagation();
		}
    });
	*/
    var show = function(picker) {
        _container.data('colorpickerembed').update(picker.getValue());
        currPicker = picker;
        colorpickerplus.show();
        //console.log('show');
    };
    var hide = function() {
        //colorpickerplus.offset({top:0, left:0});
        colorpickerplus.hide();
        currPicker = null;
    };
    var reposition = function(picker) {
	  var $element = $(picker.element);
        var offset = $element.offset();
        //var mx = offset.left+picker.element.outerHeight();
        //var my = offset.top;
        //console.log(picker.element.outerHeight());
        offset.top +=$element.outerHeight();
        colorpickerplus.css(offset);
    };
    var defaults = {};
    var ColorpickerPlus = function(element, options) {
        var $element = $(element);
        this.options = $.extend({}, defaults, $element.data(), options);        
        var input = $element.is('input') ? $element : (this.options.input ?
            $element.find(this.options.input) : false);
        if (input && (input.length === 0)) {
            input = false;
        }
        if (input !== false) {
            $element.on('focus', $.proxy(this.show, this));
			this.input = input[0];
            // $element.on({
            //     'focusout.colorpickerplus': $.proxy(this.hide, this)
            // });
        }

        if ((input === false)) {
            $element.on('click', $.proxy(this.show, this));
        }
		this.element = element;
        // $($.proxy(function() {
        //     $element.trigger('create');
        // }, this));
    };
    ColorpickerPlus.version = '0.1.0';
    ColorpickerPlus.prototype = {
        constructor: ColorpickerPlus,
        destroy: function() {
			var $element = $(this.element);
            $element.removeData('colorpickerplus').off('.colorpickerplus');
            if (this.input !== false) {
                $(this.input).off('.colorpickerplus');
            }
            $element.trigger('destroy');
        },
        reposition: function() {
        	reposition(this);
        },
        show: function() {
			var $element = $(this.element);
            this.reposition();
            $(window).on('resize.colorpickerplus', $.proxy(this.reposition, this));
            $(window.document.body).on('mouseup.colorpickerplus', $.proxy(this.hide, this));
            show(this);
            $element.trigger('showPicker',[this.getValue()]);
        },
        hide: function(e) {
			var $element = $(this.element);
			var target = $(e.target);
            var p = target.closest('.colorpicker, .colorpickerplus');
            if(p.length>0||target.is('input')) {return;}
            hide();
            $(window).off('resize.colorpickerplus');
            $(window.document.body).off('mouseup.colorpickerplus');
            $element.trigger('hidePicker',[this.getValue()]);
        },
        setValue: function(val) {
			var $element = $(this.element);
            if(!!val) {
              $element.data('cpp-color', val);
            } else {
              $element.removeData('cpp-color');
            }
            $element.trigger('changeColor',[val]);
        },
        getValue: function(defaultValue) {
			var $element = $(this.element);
            defaultValue = (defaultValue === undefined) ? '#000000' : defaultValue;
            var val;
            if (this.hasInput()) {
                val = $(this.input).val();
            } else {
                val = $element.data('cpp-color');
            }
            if ((val === undefined) || (val === '') || (val === null)) {
                // if not defined or empty, return default
                val = defaultValue;
            }
            return (typeof val==='string')?val.toUpperCase():val;
        },
        hasInput: function() {
            return (this.input !== false);
        }
    };

    $.colorpickerplus = ColorpickerPlus;

    $.fn.colorpickerplus = function(option) {
        var pickerArgs = arguments;

        return this.each(function() {
            var $this = $(this),
            inst = $this.data('colorpickerplus'),
            options = ((typeof option === 'object') ? option : {});
            if ((!inst) && (typeof option !== 'string')) {
                $this.data('colorpickerplus', new ColorpickerPlus(this, options));
            } else {
                if (typeof option === 'string') {
                    inst[option].apply(inst, Array.prototype.slice.call(pickerArgs, 1));
                }
            }
        });
    };

    $.fn.colorpickerplus.constructor = ColorpickerPlus;
}));
