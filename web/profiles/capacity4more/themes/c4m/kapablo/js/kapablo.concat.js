/**
 * @file
 * Kapablo theme global behaviours.
 */

(function ($) {

    Drupal.behaviors.discussionFormClasses = {
        attach: function (context, settings) {
            $('#edit-c4m-discussion-type-und').addClass('row');

            var $discussionTypes = $('#edit-c4m-discussion-type input[type="radio"]');
            $discussionTypes.each(function () {
                if ($(this).is(':checked')) {
                    $(this).parent().addClass('active');
                }
                var value = $(this).attr('value');
                $(this).parent()
                    .addClass('discussion-type-button')
                    .addClass('discussion-type-' + value)
                    .parent().addClass('col-xs-6').addClass('col-sm-3');
                $(this).click(function () {
                    $discussionTypes.each(function () {
                        $(this).parent().removeClass('active');
                    });
                    $(this).parent().addClass('active');
                });
            });
        }
    };

    Drupal.behaviors.eventFormClasses = {
        attach: function (context, settings) {
            $('#edit-c4m-event-type-und').addClass('row');

            var $discussionTypes = $('#edit-c4m-event-type input[type="radio"]');
            $discussionTypes.each(function () {
                if ($(this).is(':checked')) {
                    $(this).parent().addClass('active');
                }
                var value = $(this).attr('value');
                $(this).parent()
                    .addClass('event-type-button')
                    .addClass('event-type-' + value)
                    .parent().addClass('col-xs-4');
                $(this).click(function () {
                    $discussionTypes.each(function () {
                        $(this).parent().removeClass('active');
                    });
                    $(this).parent().addClass('active');
                });
            });
        }
    };

    Drupal.behaviors.youTubeVideo = {
        attach: function (context, settings) {
            // Inject YouTube IFrame API script.
            var tag = document.createElement('script');
            tag.src = "https://www.youtube.com/iframe_api";
            var firstScriptTag = document.getElementsByTagName('script')[0];
            firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);
        }
    };

    Drupal.behaviors.collapseExpand = {
        attach: function (context, settings) {
            $('#allGroups').on('shown.bs.collapse', function () {
                $('#toggleMyGroups').html('Show less <i class="fa fa-chevron-right"></i>');
            }).on('hidden.bs.collapse', function () {
                $('#toggleMyGroups').html('Show all <i class="fa fa-chevron-right"></i>');
            });
        }
    };

    Drupal.behaviors.sidebarCollapseExpand = {
        attach: function (context, settings) {
            var url = location.href;
            var fullscreen = _getParameter(url, 'fullscreen');

            if (fullscreen === '1') {
                collapseSidebar($('#collapse-sidebar'));
            }

            $('#collapse-sidebar').on('click', function () {
                var buttonClasses = $(this).attr("class");
                // If the button has the "collapsed" class,
                // Expand the sidebar, otherwise collapse it.
                if (buttonClasses.indexOf("collapsed") >= 0) {
                    expandSidebar($(this));
                }
                else {
                    collapseSidebar($(this));
                }
            });

            /**
             * Collapse the sidebar in the Wiki pages.
             *
             * Changes classes of the right and left column,
             * hides the content in the sidebar.
             *
             * @param button
             *  The clicked button element.
             */
            function collapseSidebar(button) {
                var groupLeft = $('.group-left');
                var groupRight = $('.group-right');
                var sidebarContent = $('.collapsible');
                button.addClass('collapsed');
                button.html('<i class="fa fa-chevron-circle-right"></i>');
                groupLeft.removeClass('col-sm-4').addClass('col-sm-1 sidebar-collapsed');
                groupRight.removeClass('col-sm-8').addClass('col-sm-11');
                sidebarContent.hide();

                var nav_links = $('.og-menu-link.wiki .c4m-book-og-menu-link, #group-pages-navigation-left .field-name-c4m-content-wiki-page-navigation a');
                var href;
                $(nav_links).each(function () {
                    href = _addParameter($(this).attr('href'), 'fullscreen', '1');
                    $(this).attr('href', href);
                });
            }

            /**
             * Expand the sidebar in the Wiki pages.
             *
             * Changes classes of the right and left column,
             * shows the content in the sidebar.
             *
             * @param button
             *  The clicked button element.
             */
            function expandSidebar(button) {
                var groupLeft = $('.group-left');
                var groupRight = $('.group-right');
                var sidebarContent = $('.collapsible');
                button.removeClass('collapsed');
                button.html('<i class="fa fa-chevron-circle-left"></i> ' + Drupal.t('Hide sidebar'));
                groupLeft.removeClass('col-sm-1 sidebar-collapsed').addClass('col-sm-4');
                groupRight.removeClass('col-sm-11').addClass('col-sm-8');
                sidebarContent.show();

                var nav_links = $('.og-menu-link.wiki .c4m-book-og-menu-link, #group-pages-navigation-left .field-name-c4m-content-wiki-page-navigation a');
                var href;
                $(nav_links).each(function () {
                    href = _removeURLParameter($(this).attr('href'), 'fullscreen');
                    $(this).attr('href', href);
                });
            }
        }
    };

    Drupal.behaviors.wikiPagesSubNavigation = {
        attach: function (context, settings) {
            var $wrapper = $('#group-pages-navigation-left');

            if ($wrapper == null) {
                return;
            }

            collapsibleNavigation($wrapper.find('ul[role="menu"]'));

            // .wrapInner() does not retain bound events.
            var wrapper = $wrapper.get(0);

            if (wrapper == null) {
                return;
            }

            // Don't animate multiple times.
            if (!wrapper.animating || wrapper.animating == null) {
                wrapper.animating = true;
                var speed = $wrapper.hasClass('speed-fast') ? 300 : 1000;
                if ($wrapper.hasClass('effect-none') && $wrapper.hasClass('speed-none')) {
                    $('> .field-group-format-wrapper', wrapper).toggle();
                }
                else if ($wrapper.hasClass('effect-blind')) {
                    $('> .field-group-format-wrapper', wrapper).toggle('blind', {}, speed);
                }
                else {
                    $('> .field-group-format-wrapper', wrapper).toggle(speed);
                }
                wrapper.animating = false;
                $wrapper.toggleClass('collapsed');

                return false;
            }
        }
    };

    Drupal.behaviors.readMoreProject = {
        attach: function (context, settings) {
            var readMore = $(".group-readmore");
            var link = "<a class=\"readmore-text readmore-text--showmore\" data-toggle=\"collapse\" href=\"#readmorecontent\" aria-expanded=\"false\" aria-controls=\"readmorecontent\">Show more</a>";

            readMore.after(link);

            $(".readmore-text").on("click", function () {
                "use strict";
                if ($(this).hasClass("readmore-text--showmore")) {
                    $(this).text("Show less");
                    $(this).toggleClass("readmore-text--showmore");
                }
                else {
                    $(this).text("Show more");
                    $(this).toggleClass("readmore-text--showmore");
                }
            });
        }
    };

    Drupal.behaviors.initTooltips = {
        attach: function (context, settings) {
            var tooltips = $('[data-toggle="tooltip"]');
            tooltips.tooltip();
        }
    };

    Drupal.behaviors.initDropdowns = {
        attach: function (context, settings) {
            $('.dropdown-toggle').dropdown();
        }
    };

    Drupal.behaviors.jumpToTitle = {
        attach: function (context, settings) {
            // Do this only once.
            if (context !== document) {
                return;
            }

            if (settings.c4m && !settings.c4m.jumpToTitle) {
                return;
            }

            // We have to use setTimeout because:
            // - for some reason when attaching the behaviour h1 has the scroll top
            //   value of 0. Only on $(document).ready() it has the right value.
            // - we have to let admin menu to do its thing.
            var timeout = 0;
            var $body = $('body');
            if ($body.hasClass('admin-menu')) {
                timeout = 500;
            }

            setTimeout(function () {
                // Don't do anything if the user already scrolled to a different
                // position.
                if ($body.scrollTop() !== 0) {
                    return;
                }
                $('html, body').animate({
                    scrollTop: parseInt($('h1').offset().top) + 'px'
                }, 100);
            }, timeout);
        }
    };

    Drupal.behaviors.fixLeafletMaps = {
        attach: function (context, settings) {
            setTimeout(function () {
                if (typeof settings.leaflet != 'undefined' && settings.leaflet instanceof Array) {
                    settings.leaflet[0].lMap.invalidateSize(false);
                }
            }, 100);
        }
    };

    Drupal.behaviors.registration = {
        attach: function (context, settings) {
            $('.use-another-email', context).click(function () {
                $('input[name="mail"]').val('').focus();
                return false;
            });

            $('#user-register-form').submit(function () {
                $(':disabled', this).prop('disabled', false);
            });
        }
    };

    $(window).bind("load", function () {
        // After ajax processing, the form often gets the id "user-register--2" or similar.
        $('[id^=user-register] input[name="mail"]').focus();
    });

    // Disable form buttons on AJAX calls.
    $(document)
        .ajaxStart(function () {
            $('.form-submit').addClass('drupal-ajax-disabled').attr('disabled', 'disabled');
        })
        .ajaxComplete(function () {
            $('.drupal-ajax-disabled').removeAttr('disabled');
        });

    function collapsibleNavigation(element) {
        var element = $(element);

        element.find('li.expanded').each(function (index, el) {
            var el = $(el);
            var subnav = el.find('> .collapse');
            if (subnav.hasClass('in')) {
                el.find('> a > i').removeClass('fa-caret-right').addClass('fa-caret-down');
            }
        });

        element.find('[data-toggle="collapse"]').on('click', function (e) {
            e.preventDefault();

            var $this = $(this);

            var target = $this.data('target');
            var sub_navigation = $(target);

            sub_navigation.toggleClass('in');

            if ($this.hasClass('fa-caret-right')) {
                $this.removeClass('fa-caret-right');
                $this.addClass('fa-caret-down');
            }
            else if ($this.hasClass('fa-caret-down')) {
                $this.removeClass('fa-caret-down');
                $this.addClass('fa-caret-right');
            }

            return false;
        });
    }

    /**
     * Remove a parameter from an URL string.
     *
     * @param url
     *   Url or path to remove parameter from.
     * @param parameter
     *   Name of the parameter to remove.
     *
     * @returns {*}
     *
     * @private
     */
    function _removeURLParameter(url, parameter) {
        // Prefer to use l.search if you have a location/link object.
        var urlparts = url.split('?');
        if (urlparts.length >= 2) {

            var prefix = encodeURIComponent(parameter) + '=';
            var pars = urlparts[1].split(/[&;]/g);

            // Reverse iteration as may be destructive.
            for (var i = pars.length; i-- > 0;) {
                // Idiom for string.startsWith.
                if (pars[i].lastIndexOf(prefix, 0) !== -1) {
                    pars.splice(i, 1);
                }
            }

            if (pars.length > 0) {
                url = urlparts[0] + '?' + pars.join('&');
            }
            else {
                url = urlparts[0];
            }

            return url;
        }
        else {
            return url;
        }
    }

    /**
     * Add a parameter to an URL string.
     *
     * @param url
     *   Url or path to add parameter to.
     * @param parameterName
     *   Name of the parameter to add.
     * @param parameterValue
     *   Value to give the parameter.
     *
     * @returns {string}
     *
     * @private
     */
    function _addParameter(url, parameterName, parameterValue) {
        var replaceDuplicates = true;
        var urlhash;
        var cl;

        if (url.indexOf('#') > 0) {
            cl = url.indexOf('#');
            urlhash = url.substring(url.indexOf('#'), url.length);
        }
        else {
            urlhash = '';
            cl = url.length;
        }
        var sourceUrl = url.substring(0, cl);

        var urlParts = sourceUrl.split("?");
        var newQueryString = "";

        if (urlParts.length > 1) {
            var parameters = urlParts[1].split("&");
            for (var i = 0; (i < parameters.length); i++) {
                var parameterParts = parameters[i].split("=");
                if (!(replaceDuplicates && parameterParts[0] === parameterName)) {
                    if (newQueryString === "") {
                        newQueryString = "?";
                    }
                    else {
                        newQueryString += "&";
                    }
                    newQueryString += parameterParts[0] + "=" + (parameterParts[1] ? parameterParts[1] : '');
                }
            }
        }
        if (newQueryString === "") {
            newQueryString = "?";
        }

        if (newQueryString !== "" && newQueryString !== '?') {
            newQueryString += "&";
        }
        newQueryString += parameterName + "=" + (parameterValue ? parameterValue : '');
        return urlParts[0] + newQueryString + urlhash;
    };

    function _getParameter(url, parameter) {
        var urlParts = url.split("?");

        if (urlParts.length > 1) {
            var parameters = urlParts[1].split("&");
            for (var i = 0; (i < parameters.length); i++) {
                var parameterParts = parameters[i].split("=");
                if (parameterParts[0] === parameter) {
                    return parameterParts[1];
                }
            }
        }
    };

})
(jQuery);

/**
 * @file
 * @file!
 * classie - class helper functions
 * from bonzo https://github.com/ded/bonzo.
 *
 * Classie.has( elem, 'my-class' ) -> true/false
 * classie.add( elem, 'my-new-class' )
 * classie.remove( elem, 'my-unwanted-class' )
 * classie.toggle( elem, 'my-class' )
 */

/*jshint browser: true, strict: true, undef: true */
/*global define: false */

(function (window) {

    'use strict';

  // Class helper functions from bonzo https://github.com/ded/bonzo
  function classReg(className) {
      return new RegExp("(^|\\s+)" + className + "(\\s+|$)");
  }

  // classList support for class management
  // altho to be fair, the api sucks because it won't accept multiple classes at once.
    var hasClass, addClass, removeClass;

  if ('classList' in document.documentElement) {
      hasClass = function (elem, c) {
          return elem.classList.contains(c);
      };
      addClass = function (elem, c) {
          elem.classList.add(c);
      };
      removeClass = function (elem, c) {
          elem.classList.remove(c);
      };
  }
  else {
      hasClass = function (elem, c) {
          return classReg(c).test(elem.className);
      };
      addClass = function (elem, c) {
        if (!hasClass(elem, c)) {
            elem.className = elem.className + ' ' + c;
        }
      };
      removeClass = function (elem, c) {
          elem.className = elem.className.replace(classReg(c), ' ');
      };
  }

  function toggleClass(elem, c) {
      var fn = hasClass(elem, c) ? removeClass : addClass;
      fn(elem, c);
  }

    var classie = {
        // Full names.
        hasClass: hasClass,
        addClass: addClass,
        removeClass: removeClass,
        toggleClass: toggleClass,
        // Short names.
        has: hasClass,
        add: addClass,
        remove: removeClass,
        toggle: toggleClass
    };

  // Transport.
  if (typeof define === 'function' && define.amd) {
      // AMD.
      define(classie);
  }
  else {
      // Browser global.
      window.classie = classie;
  }

})(window);

/**
 * @file
 */

(function () {

  Drupal.behaviors.sideBarEffects = {
    attach: function (context, settings) {

      function hasParentClass(e, classname) {
        if (e === document) {
          return false;
        }
        if (window.classie.has(e, classname)) {
          return true;
        }
        return e.parentNode && hasParentClass(e.parentNode, classname);
      }

      // http://coveroverflow.com/a/11381730/989439
      function mobilecheck() {
        var check = false;
        (function (a) {if (/(android|ipad|playbook|silk|bb\d+|meego).+mobile|avantgo|bada\/|blackberry|blazer|compal|elaine|fennec|hiptop|iemobile|ip(hone|od)|iris|kindle|lge |maemo|midp|mmp|netfront|opera m(ob|in)i|palm( os)?|phone|p(ixi|re)\/|plucker|pocket|psp|series(4|6)0|symbian|treo|up\.(browser|link)|vodafone|wap|windows (ce|phone)|xda|xiino/i.test(a)||/1207|6310|6590|3gso|4thp|50[1-6]i|770s|802s|a wa|abac|ac(er|oo|s\-)|ai(ko|rn)|al(av|ca|co)|amoi|an(ex|ny|yw)|aptu|ar(ch|go)|as(te|us)|attw|au(di|\-m|r |s )|avan|be(ck|ll|nq)|bi(lb|rd)|bl(ac|az)|br(e|v)w|bumb|bw\-(n|u)|c55\/|capi|ccwa|cdm\-|cell|chtm|cldc|cmd\-|co(mp|nd)|craw|da(it|ll|ng)|dbte|dc\-s|devi|dica|dmob|do(c|p)o|ds(12|\-d)|el(49|ai)|em(l2|ul)|er(ic|k0)|esl8|ez([4-7]0|os|wa|ze)|fetc|fly(\-|_)|g1 u|g560|gene|gf\-5|g\-mo|go(\.w|od)|gr(ad|un)|haie|hcit|hd\-(m|p|t)|hei\-|hi(pt|ta)|hp( i|ip)|hs\-c|ht(c(\-| |_|a|g|p|s|t)|tp)|hu(aw|tc)|i\-(20|go|ma)|i230|iac( |\-|\/)|ibro|idea|ig01|ikom|im1k|inno|ipaq|iris|ja(t|v)a|jbro|jemu|jigs|kddi|keji|kgt( |\/)|klon|kpt |kwc\-|kyo(c|k)|le(no|xi)|lg( g|\/(k|l|u)|50|54|\-[a-w])|libw|lynx|m1\-w|m3ga|m50\/|ma(te|ui|xo)|mc(01|21|ca)|m\-cr|me(rc|ri)|mi(o8|oa|ts)|mmef|mo(01|02|bi|de|do|t(\-| |o|v)|zz)|mt(50|p1|v )|mwbp|mywa|n10[0-2]|n20[2-3]|n30(0|2)|n50(0|2|5)|n7(0(0|1)|10)|ne((c|m)\-|on|tf|wf|wg|wt)|nok(6|i)|nzph|o2im|op(ti|wv)|oran|owg1|p800|pan(a|d|t)|pdxg|pg(13|\-([1-8]|c))|phil|pire|pl(ay|uc)|pn\-2|po(ck|rt|se)|prox|psio|pt\-g|qa\-a|qc(07|12|21|32|60|\-[2-7]|i\-)|qtek|r380|r600|raks|rim9|ro(ve|zo)|s55\/|sa(ge|ma|mm|ms|ny|va)|sc(01|h\-|oo|p\-)|sdk\/|se(c(\-|0|1)|47|mc|nd|ri)|sgh\-|shar|sie(\-|m)|sk\-0|sl(45|id)|sm(al|ar|b3|it|t5)|so(ft|ny)|sp(01|h\-|v\-|v )|sy(01|mb)|t2(18|50)|t6(00|10|18)|ta(gt|lk)|tcl\-|tdg\-|tel(i|m)|tim\-|t\-mo|to(pl|sh)|ts(70|m\-|m3|m5)|tx\-9|up(\.b|g1|si)|utst|v400|v750|veri|vi(rg|te)|vk(40|5[0-3]|\-v)|vm40|voda|vulc|vx(52|53|60|61|70|80|81|83|85|98)|w3c(\-| )|webc|whit|wi(g |nc|nw)|wmlb|wonu|x700|yas\-|your|zeto|zte\-/i.test(a.substr(0,4))) {
            check = true
        }
        })(navigator.userAgent||navigator.vendor||window.opera);
        return check;
      }

      function init() {

        var container = document.getElementsByClassName('page-container').item(0),
          reset = document.getElementById('closeMenu'),
          buttons = Array.prototype.slice.call(document.querySelectorAll('.js-navigationButton')),
        // Event type (if mobile use touch events)
          eventtype = mobilecheck() ? 'touchstart' : 'click',
          resetMenu = function () {
            window.classie.remove(container, 'offCanvasNavigation--visible');
          },
          bodyClickFn = function (evt) {
            if (!hasParentClass(evt.target, 'offCanvasNavigation')
              && !hasParentClass(evt.target, 'offCanvasNavigation--left')
              && !hasParentClass(evt.target, 'group-right')) {
              resetMenu();
              document.removeEventListener(eventtype, bodyClickFn);
            }
          },
          resetClickFn = function (evt) {
            if (evt.target == reset) {
              resetMenu();
              document.removeEventListener(eventtype, bodyClickFn);
            }
          };

        buttons.forEach(function (el, i) {

          var effect = el.getAttribute('data-effect');

          el.addEventListener(eventtype, function (ev) {

            ev.stopPropagation();
            ev.preventDefault();

            // Clear.
            container.className = 'page-container';
            window.classie.addClass(container, effect);
            setTimeout(function () {
              window.classie.addClass(container, 'offCanvasNavigation--visible');
            }, 25);
            document.addEventListener(eventtype, bodyClickFn);
            document.addEventListener(eventtype, resetClickFn);
          });
        });

      }

      init();

    }
  }
})();

//# sourceMappingURL=kapablo.concat.js.map