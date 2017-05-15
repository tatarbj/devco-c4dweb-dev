/**
 * c4m-app
 * @version v0.0.1 - 2017-05-05
 * @link 
 * @author  <>
 * @license MIT License, http://www.opensource.org/licenses/MIT
 */
'use strict';

angular.module('c4mApp', [
  'ui.select2',
  'ui.bootstrap',
  'angularFileUpload',
  'ngAnimate',
  'angular-carousel',
  'ngTouch'
], function ($httpProvider) {

  // Use x-www-form-urlencoded Content-Type.
  $httpProvider.defaults.headers.post['Content-Type'] =
    'application/x-www-form-urlencoded;charset=utf-8';
});

'use strict';

angular.module('c4mApp')
  .controller('ActivityCtrl', function ($scope, DrupalSettings, EntityResource, $timeout, $interval, $sce) {

    /*
     * Init the Bootstrap tooltips.
     */
    $scope.bindBoostrapTooltips = function () {
      // Delay 100ms and allow all items to be added to the DOM before
      // initializing the tooltips.
      $timeout(function () {
        angular.element('[data-toggle="tooltip"]').tooltip();
      }, 100);
    };

    // Get the current group ID.
    $scope.group = DrupalSettings.getData('entity').group;

    $scope.topics = DrupalSettings.getData('request').topics;

    $scope.homepage = DrupalSettings.getData('request').homepage;

    $scope.homepage = $scope.homepage === undefined ? 0 : $scope.homepage;

    $scope.hideArticles = DrupalSettings.getData('request').hide_articles;

    $scope.hideArticles = $scope.hideArticles === undefined ? 0 : $scope.hideArticles;

    // Getting the activity stream.
    $scope.existingActivities = DrupalSettings.getActivities();

    // Init the bootstrap tooltips.
    $scope.bindBoostrapTooltips();

    // Empty new activities.
    $scope.newActivities = [];

    // Activity stream status, refresh time.
    $scope.stream = {
      // The first one is the last loaded activity, (if no activities, insert 0).
      lastLoadedTimestamp: $scope.existingActivities.length > 0 ? $scope.existingActivities[0].timestamp : 0,
      // The Timestamp of the last activity in the activity stream (bottom) which has the lowest Timestamp (if no activities, insert 0).
      firstLoadedTimestamp: $scope.existingActivities.length > 0 ? $scope.existingActivities[$scope.existingActivities.length - 1].timestamp : 0,
      status: 0
    };

    // Range of the initial loaded activity stream.
    $scope.range = 10;

    // Display the "show more" button only if the activity stream is equal to the the range.
    $scope.showMoreButton = $scope.existingActivities.length >= $scope.range;

    // Refresh rate of the activity stream (60000 is one minute).
    // @TODO: Import the refresh rate from the drupal settings.
    $scope.refreshRate = 60000;

    /**
     * Refreshes the activity stream.
     *
     * The refresh rate is scope.refreshRate.
     */
    $scope.refresh = function () {
      $scope.addNewActivities('newActivities');
    };
    // Start the activity stream refresh.
    $scope.refreshing = $interval($scope.refresh, $scope.refreshRate);

    /**
     * Adds newly fetched activities.
     *
     * To either to the activity-stream or the load button.
     * Depending on if the current user added an activity or it's fetched from
     * the server.
     *
     * @param type
     *  Determines to which variable the new activity should be added,
     *  existingActivities: The new activity will be added straight to the
     *                      activity stream. (Highlighted as well)
     *  newActivities: The "new posts" notification button will appear in the
     *                 user's activity stream.
     */
    $scope.addNewActivities = function (type) {
      if (type == 'existingActivities') {
        // Merge all the loaded activities before adding the created one.
        $scope.showNewActivities(0);
      }

      var activityStreamInfo = {
        group: $scope.group,
        lastTimestamp: $scope.stream.lastLoadedTimestamp,
        homepage: $scope.homepage,
        hideArticles: $scope.hideArticles,
        topics: $scope.topics
      };

      // Don't send a request when data is missing.
      if (!activityStreamInfo.lastTimestamp || !activityStreamInfo.group) {
        // If last Timestamp is 0, this is a new group and there are no activities.
        if (activityStreamInfo.lastTimestamp != 0) {
          $scope.stream.status = 500;
          return false;
        }
      }

      // Call the update stream method.
      EntityResource.updateStream(activityStreamInfo, 'update')
        .success(function (data, status) {
          // Update the stream status.
          $scope.stream.status = status;

          // Update if there's new activities.
          if (data.data) {
            if (data.data.length == 0) {
              return;
            }
            // Count the activities that were fetched.
            var position = 0;
            angular.forEach(data.data, function (activity) {
              this.splice(position, 0, {
                id: activity.id,
                timestamp: activity.timestamp,
                html: $sce.trustAsHtml(activity.html)
              });
              position++;
            }, $scope[type]);

            // Update the last loaded Timestamp.
            // Only if there's new activities from the server.
            $scope.stream.lastLoadedTimestamp = $scope[type][0].timestamp ? $scope[type][0].timestamp : $scope.stream.lastLoadedTimestamp;
          }
        })
        .error(function (data, status) {
          // Update the stream status if we get an error, This will display the error message.
          $scope.stream.status = status;
        });
    };

    /**
     * Merge the "new activity" with the existing activity stream.
     *
     * When a user has clicked on the "new posts", we grab the activities in
     * the "new activity" group and push them to the top of the
     * "existing activity", and clear the "new activity" group.
     *
     * @param position.
     *  The position in which to add the new activities.
     */
    $scope.showNewActivities = function (position) {
      angular.forEach($scope.newActivities, function (activity) {
        this.splice(position, 0, {
          id: activity.id,
          timestamp: activity.timestamp,
          html: activity.html
        });
        position++;
      }, $scope.existingActivities);
      $scope.newActivities = [];
    };

    /**
     * When clicking on the "show more" button.
     *
     * Request the next set of activities from RESTful,
     * Adds the newly loaded activity stream to the bottom of the "existingActivities" array.
     */
    $scope.showMoreActivities = function () {
      // Determine the position of the loaded activities depending on the number of the loaded page.
      var position = $scope.existingActivities.length;

      var activityStreamInfo = {
        group: $scope.group,
        firstLoadedTimestamp: $scope.stream.firstLoadedTimestamp,
        homepage: $scope.homepage,
        hideArticles: $scope.hideArticles,
        topics: $scope.topics
      };

      // Enables to design elements on loading state - such as displaying the spinner.
      angular.element('.activity-stream').addClass('loading');

      EntityResource.updateStream(activityStreamInfo, 'load')
        .success(function (data, status) {
          if (data.data) {
            angular.forEach(data.data, function (activity) {
              this.splice(position, 0, {
                id: activity.id,
                timestamp: activity.timestamp,
                html: $sce.trustAsHtml(activity.html)
              });
              position++;
            }, $scope.existingActivities);

            if (data.data.length > 0) {
              // Update the Timestamp of the last activity in the activity stream.
              $scope.stream.firstLoadedTimestamp = data.data[data.data.length - 1].timestamp;
            }

            // Keep the "show more" button, only if the remaining activities to load is more than the range.
            // The "Count" variable will go down as we are filtering with the lowest activity Timestamp.
            $scope.showMoreButton = data.data.length >= $scope.range;

            // Re-init the bootstrap tooltips for the added items.
            $scope.bindBoostrapTooltips();
          }
            // Removes loading state class.
            angular.element('.activity-stream').removeClass('loading');
        });
    };

    // Listening to broadcast for changes in the activity.
    // e.g. Adding a new activity from the "main" controller.
    $scope.$on('c4m.activity.update', function () {
      // Load new activity.
      $scope.addNewActivities('existingActivities');
    });

    // Listening to broadcast for changes in the refresh.
    // This will stop or resume the refresh of the activity stream.
    // In case of resuming the activity stream,
    // Wait for 10 seconds to avoid any conflicts between the normal refresh and the "create new activity" pull.
    $scope.$on('c4m.activity.refresh', function (broadcast, action) {
      if (action == 'stop') {
        $interval.cancel($scope.refreshing);
      }
      else {
        $timeout(function () {
          $scope.refreshing = $interval($scope.refresh, $scope.refreshRate);
        }, 10000);
      }
    });
  });

'use strict';

angular.module('c4mApp')
  .controller('CarouselCtrl', function ($scope, DrupalSettings) {
    $scope.carouselImages = DrupalSettings.getCarousels();
    $scope.carouselIndex = $scope.carouselImages.length;
  });

'use strict';

angular.module('c4mApp')
  .controller('DrupalFormCtrl', function ($scope, DrupalSettings, EntityResource, Request, $window, $document, $modal, QuickPostService, $filter, FileUpload) {

    $scope.data = DrupalSettings.getData('vocabularies');

    $scope.data.group = DrupalSettings.getData('group');

    // Get related to the discussion documents.
    $scope.data.relatedDocuments = DrupalSettings.getData('relatedDocuments');

    // Get the form Identifier, for the related documents widget.
    $scope.formId = DrupalSettings.getData('formId');

    $scope.fieldName = '';

    $scope.model = {};

    $scope.basePath = DrupalSettings.getBasePath();

    // Get the Vocabulary ID of the current group.
    $scope.tagsId = DrupalSettings.getData('tags_id');

    // Get the selected tags (Only on edit page).
    $scope.data.tags = DrupalSettings.getData('tags');

    // Get the selected values of the taxonomy-terms (Only on edit page).
    $scope.values = DrupalSettings.getData('values');

    // Assign all the vocabularies to $scope.model.
    angular.forEach($scope.data, function (values, vocab) {
      $scope.model[vocab] = {};
    });

    // When on an edit page, Add the values of the taxonomies to the $scope.model,
    // This will unable us to show the selected values when opening an edit page.
    angular.forEach($scope.values, function (values, vocab) {
      angular.forEach(values, function (value, id) {
        $scope.model[vocab][id] = value;
      });
    });

    // Creating the pop-ups according to the vocabulary that was sent to the controller.
    $scope.popups = {};
    angular.forEach($scope.data, function (value, key) {
      $scope.popups[key] = 0;
    });

    angular.forEach($scope.data.categories, function (item, value) {
      item.selected = false;
    });

    // Copy the vocabularies to another variable,
    // It can be filtered without effecting the data that was sent to the controller.
    $scope.filteredTerms = angular.copy($scope.data);

    // Check if there's categories in the current group,
    // to display an empty categories message.
    $scope.categoriesLength = angular.isDefined($scope.filteredTerms.categories) && Object.keys($scope.filteredTerms.categories).length ? true : false;

    // Update the shown taxonomies upon searching.
    $scope.updateSearch = function (vocab) {
      $scope.filteredTerms[vocab] = $filter('termsFilter')($scope.data[vocab], $scope.searchTerms[vocab]);
    };

    // Toggle the visibility of the popovers.
    $scope.togglePopover = function (name, event) {
      QuickPostService.togglePopover(name, event, $scope.popups);
    };

    // Getting matching tags.
    $scope.tagsQuery = function (query) {
      QuickPostService.tagsQuery(query, $scope);
    };

    // Watch the "Tags" variable for changes,
    // Add the selected tags to the hidden tags input,
    // This way it can be saved in the Drupal Form.
    $scope.$watch('data.tags', function () {
      var tags = [];
      angular.forEach($scope.data.tags, function (tag) {
        if (!tag.isNew) {
          tags.push(tag.text + ' (' + tag.id + ')');
        }
        else {
          tags.push(tag.text);
        }
      });
      if (!angular.isObject($scope.tagsId)) {
        angular.element('#edit-og-vocabulary-und-0-' + $scope.tagsId).val(tags.join(', '));
      }
    });

    /**
     * Update the checkboxes in the Drupal form.
     *
     * We have to fill the fields according to the name of the field because
     * It's more accurate and we have conflicting values,
     * But in the case of "og_vocab", The structure of the field name is different
     * and we update it according to the value instead.
     *
     * @param key
     *   The ID of the term that was changed.
     * @param vocab
     *   The name of the vocab.
     */
    $scope.updateSelectedTerms = function (key, vocab) {
      if ($scope.model[vocab][key]) {
        // Checkbox has been checked.
        if (vocab == 'categories') {
          angular.element('input[type=checkbox][value="' + key + '"]').prop("checked", true);
        }
        else {
          // Check up to 3 topics selected.
          if (vocab == 'c4m_vocab_topic' || vocab == 'c4m_vocab_topic_expertise' || vocab == 'c4m_vocab_geo') {
            var topicCount = 0;
            angular.forEach($scope.model[vocab], function (element, topicKey) {
              if (element === true && $scope.data[vocab][topicKey]) {
                // Term is selected and it's term of the first level.
                topicCount++;
              }
            });
            // Don't check if selected more than 3 topics.
            if (topicCount > 3) {
              $scope.model[vocab][key] = false;
              angular.element('input[type=checkbox][name="' + vocab + '[und][' + key + ']"]').prop("checked", false);
              return;
            }
          }
          angular.element('input[type=checkbox][name="' + vocab + '[und][' + key + ']"]').prop("checked", true);
        }
      }
      else {
        // Checkbox has been unchecked.
        if (vocab == 'categories') {
          angular.element('input[type=checkbox][value="' + key + '"]').prop("checked", false);
        }
        else {
          angular.element('input[type=checkbox][name="' + vocab + '[und][' + key + ']"]').prop("checked", false);
        }
        if (key in $scope.data[vocab]) {
          // This is the 1st level term - should uncheck all 2 an 3 levels terms.
          angular.forEach($scope.data[vocab][key].children, function (child, itemKey) {
            var childID = child.id;

            // Uncheck 2 level terms.
            if (childID in $scope.model[vocab] && $scope.model[vocab][childID] === true) {
              $scope.model[vocab][childID] = false;
              if (vocab == 'categories') {
                angular.element('input[type=checkbox][value="' + childID + '"]').prop("checked", false);
              }
              else {
                angular.element('input[type=checkbox][name="' + vocab + '[und][' + childID + ']"]').prop("checked", false);
              }
              // Uncheck 3 level terms.
              angular.forEach($scope.data[vocab][key].children[itemKey].children, function (childChild, childChildKey) {
                var childChildID = childChild.id;
                if (childChildID in $scope.model[vocab] && $scope.model[vocab][childChildID] === true) {
                  $scope.model[vocab][childChildID] = false;
                  if (vocab == 'categories') {
                    angular.element('input[type=checkbox][value="' + childChildID + '"]').prop("checked", false);
                  }
                  else {
                    angular.element('input[type=checkbox][name="' + vocab + '[und][' + childChildID + ']"]').prop("checked", false);
                  }
                }
              });
            }
          });
        }
        else {
          // This was the 2 or 3 level term.
          angular.forEach($scope.data[vocab], function (term, termKey) {
            angular.forEach($scope.data[vocab][termKey].children, function (child, childKey) {
              if (key == child.id) {
                // This is the current 2 level term - should uncheck its children.
                angular.forEach($scope.data[vocab][termKey].children[childKey].children, function (childChild, childChildKey) {
                  var childID = childChild.id;
                  if (childID in $scope.model[vocab] && $scope.model[vocab][childID] === true) {
                    $scope.model[vocab][childID] = false;
                    if (vocab == 'categories') {
                      angular.element('input[type=checkbox][value="' + childID + '"]').prop("checked", false);
                    }
                    else {
                      angular.element('input[type=checkbox][name="' + vocab + '[und][' + childID + ']"]').prop("checked", false);
                    }
                  }
                });
              }
            });
          });
        }
      }
    };

    /**
     * Show or hide list of subcategories for the current category.
     *
     * Is called by click.
     *
     * @param item
     *  Current category item.
     */
    $scope.updateSelected = function (item) {
      item.selected = !item.selected;
    };

    /**
     * Check if current term has at least one selected child.
     *
     * @param vocab
     *  Vocabulary name.
     * @param key
     *  1-st level term id.
     * @param childKey
     *  2-nd level term id.
     *
     * @returns {boolean}
     */
    $scope.termHasChildrenSelected = function (vocab, key, childKey) {
      if (childKey != 'null') {
        // This is 2-level term.
        if (!$scope.data[vocab][key].children[childKey]) {
          // This term has been removed.
          return false;
        }
        if (!$scope.data[vocab][key].children[childKey].children) {
          // This term doesn't have children at all.
          return false;
        }
        for (var i = 0; i < $scope.data[vocab][key].children[childKey].children.length; i++) {
          var id = $scope.data[vocab][key].children[childKey].children[i].id;
          if ($scope.model[vocab][id] === true) {
            return true;
          }
        }
      }
      else {
        // This is 1-level term.
        if (!$scope.data[vocab][key]) {
          // This term has been removed.
          return false;
        }
        if (!$scope.data[vocab][key].children) {
          // This term doesn't have children at all.
          return false;
        }
        for (var i = 0; i < $scope.data[vocab][key].children.length; i++) {
          var id = $scope.data[vocab][key].children[i].id;
          if ($scope.model[vocab][id] === true) {
            return true;
          }
        }
      }
      return false;
    };

    /**
     * When clicking on the "X" next to the taxonomy-term name (full form page).
     *
     * @param key
     *  The ID of the taxonomy.
     * @param vocab
     *  The name of the vocabulary.
     */
    $scope.removeTaxonomyValue = function (key, vocab) {
      $scope.model[vocab][key] = false;
      $scope.updateSelectedTerms(key, vocab);
    };

    // Close all popovers on "ESC" key press.
    $document.on('keyup', function (event) {
      // 27 is the "ESC" button.
      if (event.which == 27) {
        $scope.closePopups();
      }
    });

    // Close all popovers on click outside popup box.
    $document.on('mousedown', function (event) {
      // Check if we are not clicking on the popup.
      var parents = angular.element(event.target).parents();
      var close = true;
      angular.forEach(parents, function (parent, id) {
        if (parent.className.indexOf('popover') != -1) {
          close = false;
        }
      });
      // This is not button, that should open popup.
      if (event.target.type != 'button' && close) {
        $scope.closePopups();
      }
    });

    /**
     * Make all popups closed.
     */
    $scope.closePopups = function () {
      $scope.$apply(function (scope) {
        angular.forEach($scope.popups, function (value, key) {
          this[key] = 0;
        }, $scope.popups);
      });
    };

    /**
     * Uploading document file.
     *
     * @param $files
     *  The file.
     * @param fieldName
     *  Name of the current field.
     */
    $scope.onFileSelect = function ($files, fieldName) {
      $scope.setFieldName(fieldName);
      // $files: an array of files selected, each file has name, size, and type.
      for (var i = 0; i < $files.length; i++) {
        var file = $files[i];
        FileUpload.upload(file).then(function (data) {
          var fileId = data.data.data[0].id;
          $scope.data.fileName = data.data.data[0].label;
          $scope.serverSide.file = data;
          var openPath = DrupalSettings.getData('purl') == $scope.basePath ? $scope.basePath : DrupalSettings.getData('purl') + '/';
          Drupal.overlay.open(openPath + 'overlay-file/' + fileId + '?render=overlay');
        });
      }
    };

    /**
     * Opens the system's file browser.
     */
    $scope.browseFiles = function (fieldName) {
      angular.element('#' + fieldName).click();
    };

    /**
     * Set the name of the current field.
     *
     * @param fieldName
     */
    $scope.setFieldName = function (fieldName) {
      $scope.fieldName = fieldName;
    };
  });

'use strict';

angular.module('c4mApp')
  .controller('MainCtrl', function ($rootScope, $scope, DrupalSettings, GoogleMap, EntityResource, Request, $window, $document, QuickPostService, FileUpload) {
    $scope.editorOptions = {
      resize_minHeight : 300,
      height: 200
    };
    $scope.data = DrupalSettings.getData('entity');

    // Getting the resources information.
    $scope.resources = DrupalSettings.getResources();
    $scope.resourceSpinner = false;

    if ($scope.resources) {
        // Setting empty default resource.
        $scope.selectedResource = '';
    }

    // Getting the fields information.
    $scope.fieldSchema = {};

    // Hide quickpost title field placeholder on focus.
    $scope.titlePlaceholder = true;
    $scope.titlePlaceholderText = 'Share information or an idea, start debate or ask a question here...';

    $scope = QuickPostService.setDefaults($scope);

    /**
     * Prepares the referenced "data" to be objects and normal field to be empty.
     *
     * Responsible for toggling the visibility of the taxonomy-terms checkboxes.
     * Set "popups" to 0, as to hide all of the pop-overs on load.
     *
     * @param resource_name
     *   The name of the resource.
     */
    function initFormValues(resource_name) {
      $scope.popups = {};

      angular.forEach($scope.fieldSchema.resources[resource_name], function (data, field) {
        // Don't change the group field Or resource object.
        if (field == 'resources' || field == 'group' || field == "tags") {
          return;
        }
        var allowedValues = field == "categories" ? $scope.fieldSchema.categories : data.form_element.allowed_values;

        if (angular.isObject(allowedValues)) {
          $scope.referenceValues[field] = allowedValues;
          $scope.popups[field] = 0;
          $scope.data[field] = {};
        }
      });

      $scope = QuickPostService.formatTermFieldsAsTree($scope);

      // Set "Start a Debate" as default discussion type.
      $scope.data.discussion_type = 'info';

      // Set "Event" as default event type.
      $scope.data.event_type = 'event';

      // Reset all the text fields.
      var textFields = ['label', 'body', 'tags', 'organiser' , 'datetime'];
      angular.forEach(textFields, function (field) {
        $scope.data[field] = field == 'tags' ? [] : '';
      });

      $scope.data['add_to_library'] = 1;

      // Uncheck notification checkbox.
      $scope.data.notification = false;

      // Default location is empty.
      $scope.data.location = {};
      $scope.data.location.street = '';
      $scope.data.location.city = '';
      $scope.data.location.postal_code = '';
      $scope.data.location.country_name = '';
      $scope.data.location.location_name = '';
    }

    /**
     * Getting matching tags.
     *
     * @param query
     *  The query input by the user.
     */
    $scope.tagsQuery = function (query) {
      QuickPostService.tagsQuery(query, $scope);
    };

    /**
     * Called by the directive "bundle-select".
     *
     * Updates the bundle of the entity to send to the correct API url.
     *
     * @param resource
     *  The resource name.
     *  @param event
     *    The event where the function was called.
     */
    $scope.updateResource = function (resource, event) {
      // When clicking on the "label" input
      // and the resource is already selected, Do nothing.
      if (angular.isDefined(event) && $scope.selectedResource) {
        return false;
      }
      // Empty fields info.
      $scope.fieldSchema = {};
      $scope.referenceValues = {};
      // If resource is selected, Close form.
      if ($scope.selectedResource == resource) {
        $scope.selectedResource = '';
        return false;
      }
      $scope.resourceSpinner = true;
      // Update Bundle,
      // Update the fields information for this resource.
      DrupalSettings.getFieldSchema(resource)
        .success(function (data) {
          $scope.fieldSchema = data.c4m.field_schema;
          $scope.data.entity = data.c4m.data.entity;
          initFormValues(resource);
          $scope.selectedResource = resource;
          $scope.resourceSpinner = false;
        });
    };

    /**
     * Helper function to manage the flow of focusing the quick post title.
     *
     * When focusing the quick post title we should hide the placeholder from
     * it and try to update the resource.
     *
     * @see $scope.updateResource()
     */
    $scope.focusQuickPostTitle = function (resource, event) {
      $scope.titlePlaceholder = false;
      $scope.updateResource(resource, event);
    };

    /**
     * Remove taxonomy term from the data.
     *
     * Called by click on added term.
     *
     * @param key
     *  taxonomy term id
     * @param field
     *  name of the taxonomy terms field.
     */
    $scope.removeTaxonomyValue = function (key, field) {
      $scope.data[field][key] = false;

      angular.forEach($scope[field], function (term, id) {
        // Go through all 1 level terms.
        angular.forEach($scope[field][id].children, function (child, childKey) {
          var childID = child.id;
          // If removed current 1 level term - all 2 and 3 level terms will be removed.
          // If removed current 2 level term - all 3 level terms will be removed.
          if (id == key || childID == key) {
            if (childID in $scope.data[field] && $scope.data[field][childID] === true) {
              $scope.data[field][childID] = false;
            }
            angular.forEach($scope[field][id].children[childKey].children, function (childChild, childChildKey) {
              var childChildID = childChild.id;
              if (childChildID in $scope.data[field] && $scope.data[field][childChildID] === true) {
                $scope.data[field][childChildID] = false;
              }
            });
          }
        });
      });
    };

    // Find taxonomy term name.
    $scope.findLabel = function (vocab, termID) {
      return QuickPostService.findLabel(vocab, termID);
    };

    /**
     * Called by the directive "types".
     *
     * Updates the type of the selected resource.
     *
     * @param type
     *  The type.
     * @param field
     *  The name of the field.
     */
    $scope.updateType = function (type, field) {
      // Update type field, unless its's already set to input value.
      if ($scope.data[field] != type) {
        $scope.data[field] = type;
      }
    };

    // Toggle the visibility of the popovers.
    $scope.togglePopover = function (name, event) {
      QuickPostService.togglePopover(name, event, $scope.popups);
    };

    /**
     * Check if current term has at least one selected child.
     *
     * @param vocab
     *  Vocabulary name.
     * @param key
     *  1-st level term id.
     * @param childKey
     *  2-nd level term id.
     *
     * @returns {boolean}
     */
    $scope.termHasChildrenSelected = function (vocab, key, childKey) {
      if (childKey != 'null') {
        // This is 2-level term.
        if (!$scope[vocab][key].children[childKey]) {
          // This term has been removed.
          return false;
        }
        if (!$scope[vocab][key].children[childKey].children) {
          // This term doesn't have children at all.
          return false;
        }
        for (var i = 0; i < $scope[vocab][key].children[childKey].children.length; i++) {
          var id = $scope[vocab][key].children[childKey].children[i].id;
          if ($scope.data[vocab][id] === true) {
            return true;
          }
        }
      }
      else {
        // This is 1-level term.
        if (!$scope[vocab][key]) {
          // This term has been removed.
          return false;
        }
        if (!$scope[vocab][key].children) {
          // This term doesn't have children at all.
          return false;
        }
        for (var i = 0; i < $scope[vocab][key].children.length; i++) {
          var id = $scope[vocab][key].children[i].id;
          if ($scope.data[vocab][id] === true) {
            return true;
          }
        }
      }
      return false;
    };

    // Close all popovers on "ESC" key press.
    $document.on('keyup', function (event) {
      // 27 is the "ESC" button.
      if (event.which == 27) {
        $scope.closePopups();
      }
    });

    // Close all popovers on click outside popup box.
    $document.on('mousedown', function (event) {
      // Check if we are not clicking on the popup.
      var parents = angular.element(event.target).parents();
      var close = true;
      angular.forEach(parents, function (parent, id) {
        if (parent.className.indexOf('popover') != -1) {
          close = false;
        }
      });
      // This is not button, that should open popup.
      if (event.target.type != 'button' && close) {
        $scope.closePopups();
      }
    });

    /**
     * Make all popups closed.
     */
    $scope.closePopups = function () {
      $scope.$apply(function (scope) {
        angular.forEach($scope.popups, function (value, key) {
          this[key] = 0;
        }, $scope.popups);
      });
    };

    /**
     * Submit form.
     *
     * Stops auto-refresh, Cleans fields (delete fields that doesn't belong to
     * the entity being created).
     * Adds location details (lat, lng) to the "event" entity.
     * Sends the cleaned-up data to the checkForm function for entity
     * creation.
     *
     *  @param data
     *    The submitted data.
     *  @param resource
     *    The bundle of the node submitted.
     *  @param type
     *    The type of the submission.
     */
    $scope.submitForm = function (data, resource, type) {

      // Stop the "Activity-stream" auto refresh When submitting a new activity,
      // because we don't want the auto refresh to display the activity as an old one.
      $rootScope.$broadcast('c4m.activity.refresh', 'stop');

      // Reset all errors.
      $scope.errors = {};

      // Get the fields of this resource.
      var resourceFields = $scope.fieldSchema.resources[resource];

      // Clean the submitted data, Drupal will return an error on undefined fields.
      var submitData = Request.cleanFields(data, resourceFields);

      checkForm(submitData, resource, resourceFields, type);
    };

    /**
     * Continue submitting form.
     *
     * Creates a node of the resource type. If Type of submission is
     * a full form - redirects to the created node's editing page.
     *
     * @param submitData
     *  The submitting data.
     * @param resource
     *  The bundle of the node submitted.
     * @param resourceFields
     *  The fields of the current resource.
     * @param type
     *  The type of the submission.
     */
    var checkForm = function (submitData, resource, resourceFields, type) {
      // Check for required fields.
      var errors = Request.checkRequired(submitData, resource, resourceFields);

      // Check the type of the submit.
      // Make node unpublished if requested to create in full form.
      submitData.status = type == 'full_form' ? 0 : 1;

      // Cancel submit and display errors if we have errors.
      if (Object.keys(errors).length) {
        angular.forEach(errors, function (value, field) {
          this[field] = value;
        }, $scope.errors);
        // Scroll up upon discovering an error.
        var quickPost = angular.element('#quick-post-form').offset();
        // Admins has the admin menu, so we take some extra pixels.
        var extraOffset = 50;
        angular.element('html, body').animate({scrollTop:quickPost.top - extraOffset}, '500', 'swing');
        return false;
      }

      // Call the create entity function service.
      EntityResource.createEntity(submitData, resource, resourceFields)
        .success(function (data, status) {
          // If requested to create in full form, Redirect user to the edit page.
          if (type == 'full_form') {
            var entityID = data.data[0].id;
            $window.location = DrupalSettings.getPurlPath() + "/node/" + entityID + "/edit";
          }
          else {
            $scope.serverSide.data = data;
            $scope.serverSide.status = status;

            // Scroll up upon creating a new activity.
            // Reference the point to scroll to the top of the form (Title input is at the top of the form).
            var labelInput = angular.element('#label').offset();
            angular.element('html, body').animate({scrollTop:labelInput.top}, '500', 'swing');

            // Add the newly created activity to the stream.
            // By broadcasting the update to the "activity" controller.
            $rootScope.$broadcast('c4m.activity.update');

            // Collapse the quick-post form.
            $scope.selectedResource = '';
          }
        })
        .error(function (data, status) {
          $scope.serverSide.data = data;
          $scope.serverSide.status = status;
        });

      // Reset the form, by removing existing values and allowing the user to write a new content.
      $scope.resetEntityForm();

      // Resume the "Activity-stream" auto refresh.
      $rootScope.$broadcast('c4m.activity.refresh', 'continue');
    };

    /**
     * Uploading document file.
     *
     * @param $files
     *  The file.
     */
    $scope.onFileSelect = function ($files) {
      // Reset the image error message.
      $scope.serverSide.data.imageError = false;

      // $files: an array of files selected, each file has name, size, and type.
      for (var i = 0; i < $files.length; i++) {
        var file = $files[i];
        FileUpload.upload(file).then(function (data) {
          $scope.data.document = data.data.data[0].id;
          $scope.data.fileName = data.data.data[0].label;
          $scope.serverSide.file = data;
        },
        function (errors) {
          $scope.serverSide.data.imageError = errors;
        });
      }
    };

    /**
     * Remove uploaded file.
     */
    $scope.removeUploadedFile = function () {
      angular.element('#document_file').val('');
      $scope.data.document = null;
      delete $scope.data.fileName;
      delete $scope.serverSide.file;
    };

    /**
     * Opens the system's file browser.
     */
    $scope.browseFiles = function () {
      angular.element('#document_file').click();
    };

    /**
     * Resets the quick-post form validations.
     *
     * Clears all the fields for a new entry.
     */
    $scope.resetEntityForm = function () {
      // Clear any form validation errors.
      $scope.entityForm.$setPristine();
      // Reset all errors.
      $scope.errors = {};
      // Reset all the fields.
      initFormValues();
      // Empty fields info.
      $scope.fieldSchema = {};
      $scope.referenceValues = {};
      // Remove file.
      $scope.removeUploadedFile();
    };

    /**
    * Closes quick-post form.
    */
    $scope.closeQuickPost = function () {
      // Clear all form fields.
      $scope.resetEntityForm();
      // Closes quick-post form.
      $scope.selectedResource = '';
    };

    /**
     * Uploading quick post document file.
     *
     * @param $files
     *  The file.
     * @param fieldName
     *  Name of the current field.
     */
    $scope.onQuickPostFileSelect = function ($files, fieldName) {

      $scope.setFieldName(fieldName);
      // $files: an array of files selected, each file has name, size, and type.
      for (var i = 0; i < $files.length; i++) {
        var file = $files[i];
        FileUpload.upload(file).then(function (data) {
          var fileId = data.data.data[0].id;
          $scope.data.fileName = data.data.data[0].label;
          $scope.serverSide.file = data;
          var openPath = DrupalSettings.getData('purl');
          Drupal.overlay.open(openPath + '/overlay-file/' + fileId + '/quick' + '?render=overlay');
        });
      }
    };

    /**
     * Set the name of the current field.
     *
     * @param fieldName
     */
    $scope.setFieldName = function (fieldName) {
      $scope.fieldName = fieldName;
    };

  });

angular.module('c4mApp')
  .controller('DocumentCtrl', function ($scope, DrupalSettings, EntityResource, Request) {

    $scope.data = DrupalSettings.getData('vocabularies');

    $scope.data.relatedDocuments = [];

    $scope.model = {};

    // Need to get current field name.
    var element = jQuery('.active-library-link', parent.window.document);
    $scope.fieldName = element.attr('id').replace('link-', '');

    /**
     * Create document node.
     *
     * @param event
     *  The submit event.
     * @param fileId
     *  Id of the attached file.
     * @param data
     *  The submitted data.
     * @param addToLibrary
     *  Open or not full form of adding document.
     */
    $scope.createDocument = function (event, fileId, data, addToLibrary) {
      // Preventing the form from redirecting to the "action" url.
      // We need the url in the action because of the "overlay" module.
      event.preventDefault();
      DrupalSettings.getFieldSchema('documents')
        .then(function (data) {
          $scope.fieldSchema = data.c4m.field_schema;
          $scope.data.entity = data.c4m.data.entity;

          var resourceFields = $scope.fieldSchema.resources['documents'];
          var submitData = Request.cleanFields(data, resourceFields);

          angular.forEach(resourceFields, function (data, field) {
            // Don't change the group field Or resource object.
            if (field == 'resources' || field == 'group' || field == "tags") {
              return;
            }
            var allowedValues = field == "categories" ? data.form_element.allowed_values.categories : data.form_element.allowed_values;
            if (angular.isObject(allowedValues) && Object.keys(allowedValues).length) {
              submitData[field] = {};
            }
          });

          submitData.document = fileId;
          submitData.group = DrupalSettings.getData('groupID');
          submitData.add_to_library = addToLibrary ? 1 : 0;
          submitData.label = $scope.data.label;

          EntityResource.createEntity(submitData, 'documents', resourceFields)
            .success(function (data, status) {
              var nid = data.data[0].id;

              var item = '(' + nid + ')';

              // Add the value we get in the hidden inputs in the parent page.
              var value = jQuery('#edit-' + $scope.fieldName + '-und', parent.window.document).val();
              var nids = jQuery('#input-' + $scope.fieldName, parent.window.document).val();
              if (value.indexOf(item) == -1) {
                value = value ? value + ', ' + item : item;
                nids = nids ? nids + ',' + nid : nid;
              }

              jQuery('#edit-' + $scope.fieldName + '-und', parent.window.document).val(value);
              jQuery('#input-' + $scope.fieldName, parent.window.document).val(nids).trigger('click');

              if (!addToLibrary) {
                // Save document and go to the parent page.
                parent.Drupal.overlay.close();
              }
              else {
                // Save document and go to its edit page to add more data.
                parent.Drupal.overlay.open(DrupalSettings.getData('purl') + '/overlay-node/' + nid + '/edit' + '?render=overlay');
              }
            });
        });
    };

    /**
     * Close the overlay.
     */
    $scope.closeOverlay = function () {
      parent.Drupal.overlay.close();
    };
  });

angular.module('c4mApp')
  .controller('DocumentQuickPostCtrl', function ($scope, DrupalSettings, EntityResource, Request) {

    $scope.data = DrupalSettings.getData('vocabularies');

    $scope.data.relatedDocuments = [];

    $scope.model = {};

    $scope.fieldName = 'c4m-related-document';
    $scope.formId = 'quick-post-form';

    /**
     * Create document node.
     *
     * @param event
     *  The submit event.
     * @param fileId
     *  Id of the attached file.
     * @param data
     *  The submitted data.
     * @param addToLibrary
     *  Open or not full form of adding document.
     */
    $scope.createDocument = function (event, fileId, data, addToLibrary) {
      // Preventing the form from redirecting to the "action" url.
      // We need the url in the action because of the "overlay" module.
      event.preventDefault();
      DrupalSettings.getFieldSchema('documents')
        .then(function (data) {
          $scope.fieldSchema = data.c4m.field_schema;
          $scope.data.entity = data.c4m.data.entity;

          var resourceFields = $scope.fieldSchema.resources['documents'];
          var submitData = Request.cleanFields(data, resourceFields);

          angular.forEach(resourceFields, function (data, field) {
            // Don't change the group field or resource object.
            if (field == 'resources' || field == 'group' || field == "tags") {
              return;
            }
            var allowedValues = field == "categories" ? data.form_element.allowed_values.categories : data.form_element.allowed_values;
            if (angular.isObject(allowedValues) && Object.keys(allowedValues).length) {
              submitData[field] = {};
            }
          });

          submitData.document = fileId;
          submitData.group = DrupalSettings.getData('groupID');
          submitData.add_to_library = addToLibrary ? 1 : 0;
          submitData.label = $scope.data.label;

          EntityResource.createEntity(submitData, 'documents', resourceFields)
            .success(function (data, status) {
              var nid = data.data[0].id;
              var item = '(' + nid + ')';

              jQuery('#edit-' + $scope.fieldName + '-und', parent.window.document).val(item);
              jQuery('#input-' + $scope.fieldName, parent.window.document).val(nid).trigger('click');

              if (!addToLibrary) {
                // Save document and go to the parent page.
                parent.Drupal.overlay.close();
              }
              else {
                // Save document and go to its edit page to add more data.
                parent.Drupal.overlay.open(DrupalSettings.getData('purl') + '/overlay-node/' + nid + '/edit' + '?render=overlay');
              }
            });
        });
    };

    /**
     * Close the overlay.
     */
    $scope.closeOverlay = function () {
      parent.Drupal.overlay.close();
    };
  });

'use strict';

/**
 * Provides the bundleSelect directive.
 *
 * @ngdoc directive
 *
 * @name c4mApp.directive:bundleSelect
 *
 * @description bundleSelect.
 */
angular.module('c4mApp')
  .directive('bundleSelect', function ($window, DrupalSettings) {
    return {
      templateUrl: DrupalSettings.getBasePath() + 'profiles/capacity4more/modules/c4m/restful/c4m_restful_quick_post/components/c4m-app/dist/directives/bundle-select/bundle-select.html',
      restrict: 'E',
      scope: {
        items: '=',
        selectedResource: '=',
        onChange: '=onChange'
      },
      link: function postLink(scope) {
        scope.purl = DrupalSettings.getPurlPath();
        // On changing type => update the bundleName.
        scope.updateResource = function (resource, e) {
          return scope.onChange(resource, e);
        }
      }
    };
  });

'use strict';

/**
 * Provides the calendar.
 *
 * @ngdoc directive
 *
 * @name c4mApp.directive:calendar
 *
 * @description calendar.
 */
angular.module('c4mApp')
  .directive('calendar', function ($window, DrupalSettings) {
    return {
      templateUrl: DrupalSettings.getBasePath() + 'profiles/capacity4more/modules/c4m/restful/c4m_restful_quick_post/components/c4m-app/dist/directives/calendar/calendar.html',
      restrict: 'E',
      scope: true
    };
  });

'use strict';

/**
 * Provides a list of related to the discussion documents.
 *
 * @ngdoc directive
 *
 * @name c4mApp.directive:relatedDocuments
 *
 * @description A list of related to the discussion documents.
 */
angular.module('c4mApp')
  .directive('relatedDocuments', function (DrupalSettings, $window, EntityResource, $sce) {
    return {
      templateUrl: DrupalSettings.getBasePath() + 'profiles/capacity4more/modules/c4m/restful/c4m_restful_quick_post/components/c4m-app/dist/directives/documents/documents.html',
      restrict: 'E',
      scope: {
        relatedDocuments: '=',
        formId: '=',
        fieldName: '='
      },
      link: function postLink(scope, element) {

        /**
         * Create array of related document objects.
         *
         * @param relatedDocuments
         *  List of related documents ids
         *
         * @returns {{}}
         *  Returns array of related document information objects
         */
        scope.updateDocumentsData = function (relatedDocuments) {
          var documents = {};
          angular.forEach(relatedDocuments, function (value, key) {
            // Get all field values of the document.
            EntityResource.getEntityData('documents', value).success(function (data, status) {
              documents[key] = data.data[0];
              // Format file size.
              documents[key].document.filesize = $window.filesize(documents[key].document.filesize);
            });
          });

          return documents;
        };

        // Get the click event form the overlay and update related documents.
        element.parents('#' + scope.formId).find('#input-' + scope.fieldName).on('click', function (event) {

          var val = jQuery(this).val();
          scope.$apply(function (scope) {
            var ids = val.split(',');
            scope.relatedDocuments = ids;
            scope.data = scope.updateDocumentsData(scope.relatedDocuments);
          });
        });

        scope.data = scope.updateDocumentsData(scope.relatedDocuments);

        // Updating data when added or removed item from the related documents.
        scope.$watch('relatedDocuments', function (newValue, oldValue) {
          if (newValue !== oldValue) {
            scope.data = scope.updateDocumentsData(newValue);
          }
        }, true);

        // Removing document from related documents.
        scope.removeDocument = function (id) {
          var index = scope.relatedDocuments.indexOf(id.toString());
          if (index != -1) {
            scope.relatedDocuments.splice(index, 1);
          }

          // Remove value from the widget's inputs.
          var value = angular.element('#edit-' + scope.fieldName + '-und').val();
          value = value.replace('(' + id + '), ', '');
          value = value.replace('(' + id + ')', '');

          var ids = angular.element('#input-' + scope.fieldName).val();
          ids = ids.replace(id + ',', '');
          ids = ids.replace(id, '');

          angular.element('#edit-' + scope.fieldName + '-und').val(value);
          angular.element('#input-' + scope.fieldName).val(ids);
        };
      }
    };
  });

'use strict';

/**
 * Provides a list of related to the discussion documents.
 *
 * @ngdoc directive
 *
 * @name c4mApp.directive:relatedDocuments
 *
 * @description A list of related to the discussion documents.
 */
angular.module('c4mApp')
  .directive('relatedQuickPostDocuments', function (DrupalSettings, $window, EntityResource) {
    return {
      templateUrl: DrupalSettings.getBasePath() + 'profiles/capacity4more/modules/c4m/restful/c4m_restful_quick_post/components/c4m-app/dist/directives/documents/documents.html',
      restrict: 'E',
      scope: {
        relatedDocuments: '=',
        formId: '=',
        fieldName: '='
      },
      link: function postLink(scope, element) {

        scope.fieldName = 'c4m-related-document';
        scope.formId = 'quick-post-form';

        /**
         * Create array of related document objects.
         *
         * @param relatedDocuments
         *  List of related documents ids
         *
         * @returns {{}}
         *  Returns array of related document information objects
         */
        scope.updateDocumentsData = function (relatedDocuments) {
          var documents = {};
          angular.forEach(relatedDocuments, function (value, key) {
            // Get all field values of the document.
            EntityResource.getEntityData('documents', value).success(function (data, status) {
              documents[key] = data.data[0];
              // Format file size.
              documents[key].document.filesize = $window.filesize(documents[key].document.filesize);
            });
          });
          return documents;
        };

        // Get the click event form the overlay and update related documents.
        element.parents('#' + scope.formId).find('#input-' + scope.fieldName).on('click', function (event) {
          var val = jQuery(this).val();
          scope.$apply(function (scope) {
            var ids = val.split(',');
            scope.relatedDocuments = ids;
            scope.data = scope.updateDocumentsData(scope.relatedDocuments);
          });
        });

        scope.data = scope.updateDocumentsData(scope.relatedDocuments);

        // Updating data when added or removed item from the related documents.
        scope.$watch('relatedDocuments', function (newValue, oldValue) {
          if (newValue !== oldValue) {
            scope.data = scope.updateDocumentsData(newValue);
          }
        }, true);

        // Removing document from related documents.
        scope.removeDocument = function () {
          scope.relatedDocuments = [];
          // Make sure the element is empty so we can select the same file
          // again.
          angular.element('#' + scope.fieldName).val('');
        };
      }
    };
  });

'use strict';

/**
 * Provides a list of filterable taxonomy terms.
 *
 * @ngdoc directive
 *
 * @name c4mApp.directive:listTerms
 *
 * @description A list of filterable taxonomy terms.
 */
angular.module('c4mApp')
  .directive('groupCategories', function ($window, DrupalSettings, $timeout, $filter) {
    return {
      templateUrl: DrupalSettings.getBasePath() + 'profiles/capacity4more/modules/c4m/restful/c4m_restful_quick_post/components/c4m-app/dist/directives/group-categories/group-categories.html',
      restrict: 'E',
      scope: {
        items: '=items',
        model: '=model',
        type: '@type',
        popup: '=',
        updatePopoverPosition: '='
      },
      link: function postLink(scope) {
        angular.forEach(scope.items, function (item, id) {
          item.selected = false;
        });
        // Set the filtered items to include all items at load.
        scope.$watch('items', function (items) {
          scope.filteredTerms = items;
          // Check if there's categories in the current group,
          // to display an empty categories message.
          scope.itemsLength = angular.isDefined(items) && Object.keys(items).length ? true : false;
        });
        // Filtering the items according to the value of the searchTerm input.
        scope.updateSearch = function () {
          scope.filteredTerms = $filter('termsFilter')(scope.items, scope.searchTerm);
        };

        /**
         * Show or hide list of subcategories for the current category.
         * Is called by click.
         *
         * @param item
         *  Current category item.
         */
        scope.updateSelected = function (item) {
          item.selected = !item.selected;
        };

        // Updating the popover position && No more than 3 regions can be
        // selected.
        // TODO: Stop user from selecting more values.
        scope.updateSelectedTerms = function () {
          // Update the position of the popover.
          if (scope.updatePopoverPosition) {
            scope.updatePopoverPosition(scope.type);
          }

          var selectedCount = 0;
          angular.forEach(scope.items, function (item, id) {
            if (id in scope.model && scope.model[id] === true) {
              selectedCount++;
            }
            else if (id in scope.model && scope.model[id] === false) {
              // Find all children and turn them to false.
              angular.forEach(scope.items[id].children, function (child, key) {
                var childID = child.id;
                if (childID in scope.model && scope.model[childID] === true) {
                  scope.model[childID] = false;
                }
              });
            }
          });

          if (selectedCount > 3) {
            angular.element("#" + scope.type + "_description").addClass('error-too-many-selected');
            if (scope.popup) {
              scope.popup = 0;
            }
          }
          else {
            angular.element("#" + scope.type + "_description").removeClass('error-too-many-selected');
          }
        };
      }
    };
  });

'use strict';

/**
 * Provides a list of filterable taxonomy terms.
 *
 * @ngdoc directive
 *
 * @name c4mApp.directive:listTerms
 *
 * @description A list of filterable taxonomy terms.
 */
angular.module('c4mApp')
  .directive('listTerms', function ($window, DrupalSettings, $timeout, $filter) {
    return {
      templateUrl: DrupalSettings.getBasePath() + 'profiles/capacity4more/modules/c4m/restful/c4m_restful_quick_post/components/c4m-app/dist/directives/list-terms/list-terms.html',
      restrict: 'E',
      scope: {
        items: '=items',
        model: '=model',
        type: '@type',
        popup: '=',
        updatePopoverPosition: '='
      },
      link: function postLink(scope) {
        // Set the filtered items to include all items at load.
        scope.$watch('items', function (items) {
          scope.filteredTerms = items;
        });
        // Filtering the items according to the value of the searchTerm input.
        scope.updateSearch = function () {
          scope.filteredTerms = $filter('termsFilter')(scope.items, scope.searchTerm);
        };
        // Updating the popover position && No more than 3 regions can be
        // selected.
        scope.updateSelectedTerms = function (key, vocab) {
          // Update the position of the popover.
          if (scope.updatePopoverPosition) {
            scope.updatePopoverPosition(scope.type);
          }

          var selectedCount = 0;
          angular.forEach(scope.items, function (item, id) {
            if (id in scope.model && scope.model[id] === true) {
              selectedCount++;

              angular.forEach(scope.items[id].children, function (child, key) {
                var childID = child.id;
                if (childID in scope.model && scope.model[childID] === false) {
                  // Term of 2 level has been unchecked - uncheck its children.
                  angular.forEach(scope.items[id].children[key].children, function (childChild, childkey) {
                    var childChildID = childChild.id;
                    if (childChildID in scope.model && scope.model[childChildID] === true) {
                      scope.model[childChildID] = false;
                    }
                  });
                }
              });
            }
            else if (id in scope.model && scope.model[id] === false) {
              // Find all children and turn them to false.
              angular.forEach(scope.items[id].children, function (child, key) {
                var childID = child.id;
                if (childID in scope.model && scope.model[childID] === true) {
                  scope.model[childID] = false;
                  // Find all child's children and turn them to false.
                  angular.forEach(scope.items[id].children[key].children, function (childChild, childkey) {
                    var childChildID = childChild.id;
                    if (childChildID in scope.model && scope.model[childChildID] === true) {
                      scope.model[childChildID] = false;
                    }
                  });
                }
              });
            }
            // Don't check if selected more than 3 topics or regions.
            if (scope.type == "topic" || scope.type == "geo") {
              if (selectedCount > 3) {
                scope.model[vocab.id] = false;
                angular.element("#" + scope.type + "_description").addClass('tooMany');
              }
            }
          });
        };
      }
    };
  });

'use strict';

/**
 * Provides the location field.
 *
 * @ngdoc directive
 *
 * @name c4mApp.directive:location
 *
 * @description location fields.
 */
angular.module('c4mApp')
  .directive('location', function ($window, DrupalSettings) {
    return {
      templateUrl: DrupalSettings.getBasePath() + 'profiles/capacity4more/modules/c4m/restful/c4m_restful_quick_post/components/c4m-app/dist/dist/directives/location/location.html',
      restrict: 'E',
      scope: {
        data: '='
      }
    };
  });

'use strict';

/**
 * Provides the different discussion types.
 *
 * @ngdoc directive
 *
 * @name c4mApp.directive:discussionTypes
 *
 * @description The types of the discussion.
 */
angular.module('c4mApp')
  .directive('types', function ($window, DrupalSettings) {
    return {
      templateUrl: DrupalSettings.getBasePath() + 'profiles/capacity4more/modules/c4m/restful/c4m_restful_quick_post/components/c4m-app/dist/directives/types/types.html',
      restrict: 'E',
      scope: {
        fieldSchema: '=',
        type: '=',
        field: '=',
        onChange: '=onChange',
        cols: '='
      },
      link: function postLink(scope) {
        // Get allowed values.
        scope.allowedValues = scope.fieldSchema[scope.field];
        // On changing type => update the discussion type.
        scope.updateType = function (type, field, e) {
          return scope.onChange(type, field, e);
        }
      }
    };
  });

'use strict';

/**
 * Provides the termsFilter.
 *
 * @ngdoc filter
 *
 * @name c4mApp.filter:termsFilter
 *
 * @description Filter taxonomy-terms according to the search input by the user and return filtered items.
 */
angular.module('c4mApp')
  .filter('termsFilter',[ function () {
    return function (items, searchText) {
      if (searchText) {
        var filtered = {};
        searchText = searchText.toLowerCase();
        angular.forEach(items, function (item, id) {
          // Check first level terms.
          if (item.label.toLowerCase().indexOf(searchText) >= 0) {
            // Label match - add to list and go to the next one.
            filtered[id] = {
              id: id,
              label: item.label,
              children: item.children
            };
          }
          else {
            var parentTerm = false;
            angular.forEach(item.children, function (child, childId) {
              // Label doesn't match - check second level terms.
              if (child.label.toLowerCase().indexOf(searchText) >= 0) {
                // Label match - add to list and go to the next one.
                if (!parentTerm) {
                  filtered[id] = {
                    id: id,
                    label: item.label,
                    children: []
                  };
                  parentTerm = true;
                }
                filtered[id].children.push({
                  id: child.id,
                  label: child.label,
                  children: child.children
                });
              }
              else {
                var childTerm = false;
                angular.forEach(child.children, function (childChild) {
                  if (childChild.label.toLowerCase().indexOf(searchText) >= 0) {
                    if (!parentTerm) {
                      filtered[id] = {
                        id: id,
                        label: item.label,
                        children: []
                      };
                      parentTerm = true;
                    }
                    if (!childTerm) {
                      filtered[id].children.push({
                        id: child.id,
                        label: child.label,
                        children: []
                      });
                      childTerm = true;
                    }
                    filtered[id].children[filtered[id].children.length - 1].children.push({
                      id: childChild.id,
                      label: childChild.label
                    });
                  }
                });
              }
            });
          }
        });
        return filtered;
      }
      else {
        return items;
      }
    }
  }]);

/**
 * Provides the human readable filesize.
 *
 * @ngdoc filter
 *
 * @name c4mApp.filter:termsFilter
 *
 * @description Format the bytes into a human readable string.
 */
angular.module('c4mApp')
  .filter('filesize', function () {
    var units = [
      'bytes',
      'KB',
      'MB',
      'GB',
      'TB',
      'PB'
    ];

    return function (bytes, precision) {
      if (isNaN(parseFloat(bytes)) || ! isFinite(bytes)) {
        return '?';
      }

      var unit = 0;

      while (bytes >= 1024) {
        bytes /= 1024;
        unit ++;
      }

      return bytes.toFixed(+ precision) + ' ' + units[ unit ];
    };
  });

/**
 * Provides the orderObjectBy.
 *
 * @ngdoc filter
 *
 * @name c4mApp.filter:orderObjectBy
 *
 * @description Filter objects according to one of it's fields.
 */
angular.module('c4mApp')
  .filter('orderObjectBy',[ function () {
    return function (items, field) {
      var sorted = [];
      angular.forEach(items, function (item) {
        sorted.push(item);
      });

      sorted.sort(function (a, b) {
        return (a[field] > b[field] ? 1 : -1);
      });

      return sorted;
    }
  }]);

'use strict';

/**
 * Provides a wrapper around the DrupalSettings object.
 *
 * @ngdoc service
 *
 * @name c4mApp.service:DrupalSettings
 *
 * @description Imports the settings sent from drupal.
 */
angular.module('c4mApp')
  .service('DrupalSettings', function ($window, $http, $sce, $q) {
    var self = this;

    // Wraps inside AngularJs Drupal settings global object.
    // @type {Drupal.settings}.
    this.settings = $window.Drupal.settings;

    /**
     * Get the base path of the Drupal installation.
     */
    this.getBasePath = function () {
      return (angular.isDefined(self.settings.c4m.basePath)) ? self.settings.c4m.basePath : undefined;
    };

    /**
     * Get the base path of the Group.
     */
    this.getPurlPath = function () {
      return (angular.isDefined(self.settings.c4m.purlPath)) ? self.settings.c4m.purlPath : undefined;
    };

    /**
     * Get the resources of the quick post.
     */
    this.getResources = function () {
      return (angular.isDefined(self.settings.c4m.resources)) ? self.settings.c4m.resources : undefined;
    };

    /**
     * Get the activity stream of the current group.
     */
    this.getActivities = function () {
      var activities = [];
      var rawActivities = (angular.isDefined(self.settings.c4m.activities)) ? self.settings.c4m.activities : undefined;

      // Activities HTML should be marked as trusted.
      angular.forEach(rawActivities, function (activity) {
        this.push({
          id: activity.id,
          timestamp: activity.timestamp,
          html: $sce.trustAsHtml(activity.html)
        });
      }, activities);

      return activities;
    };

    /**
     * Get the base path of the Drupal installation.
     */
    this.getCsrfToken = function () {
      return (angular.isDefined(self.settings.c4m.csrfToken)) ? self.settings.c4m.csrfToken : undefined;
    };

    /**
     * Get the debug status of the Drupal installation.
     */
    this.getCarousels = function () {
      return (angular.isDefined(self.settings.c4m.carousels)) ? self.settings.c4m.carousels : undefined;
    };

    /**
     * Get the debug status of the Drupal installation.
     */
    this.getFieldSchema = function (resourceName) {
      if (resourceName == 'documents') {
        var defer = $q.defer();
        defer.resolve(this.settings);

        return defer.promise;
      }
      else {
        var url = this.getPurlPath() + '/quick-post/' + resourceName + '/field-schema';

        return $http({
          method: 'GET',
          url: url,
          withCredentials: true
        });
      }
    };

    /**
     * Return the form schema.
     *
     * @param int id
     *   The form ID.
     *
     * @returns {*}
     *   The form schema if exists, or an empty object.
     */
    this.getData = function (id) {
      if (!angular.isDefined(self.settings.c4m.data)) {
        return {};
      }
      return (angular.isDefined(self.settings.c4m.data[id])) ? self.settings.c4m.data[id] : {};
    }
  });

'use strict';

/**
 * Provides the EntityResource service.
 *
 * @ngdoc service
 *
 * @name c4mApp.service:EntityResource
 *
 * @description Sends the request to RESTful.
 */
angular.module('c4mApp')
  .service('EntityResource', function (DrupalSettings, Request, $http) {

    /**
     * Get the entity by id.
     *
     * @param resource
     *  The bundle of the entity
     * @param entityId
     *  The node id.
     *
     * @returns {*}
     *  JSON of the entity.
     */
    this.getEntityData = function (resource, entityId) {
      var url = DrupalSettings.getBasePath() + 'api/' + resource;

      try {
        // Verify we have entity and group IDs to proceed.
        if (entityId && Drupal.settings.c4m.data.group) {
          url += '/' + entityId + '?group=' + Drupal.settings.c4m.data.group;
        }
      }
      catch (e) {
      }

      return $http({
        method: 'GET',
        url: url,
        withCredentials: true
      });
    };

    /**
     * Create a new entity.
     *
     * @param data
     *   The data object to POST.
     * @param resource
     *   The bundle of the entity.
     * @param resourceFields
     *   The fields information.
     * @param entityId
     *   The editing node id or NULL.
     *
     * @returns {*}
     *   JSON of the newly created entity.
     */
    this.createEntity = function (data, resource, resourceFields, entityId) {

      Request.resourceFields = resourceFields;
      Request.resource = resource;

      var url = DrupalSettings.getBasePath() + 'api/' + resource;

      if (entityId) {
        url += '/' + entityId;
      }

      return $http({
        method: entityId ? 'PATCH' : 'POST',
        url: url,
        data: data,
        transformRequest: Request.prepare,
        headers: {
          "Content-Type": 'application/x-www-form-urlencoded',
          "X-CSRF-Token": DrupalSettings.getCsrfToken()
        },
        withCredentials: true
      });
    };

    /**
     * Update the activity stream, and Load more activities.
     *
     * Provides the 'Show more' button.
     *
     * @param data
     *   The stream data.
     * @param action
     *   The type of action requested (Update activity || Load more activity).
     *
     * @returns {*}
     *   JSON of the updated activity stream.
     */
    this.updateStream = function (data, action) {
      var config = {
        withCredentials: true,
        headers: {
          "X-CSRF-Token": DrupalSettings.getCsrfToken()
        }
      };

      var timestamp = action == 'update' ? data.lastTimestamp : data.firstLoadedTimestamp;
      var operator = action == 'update' ? '>' : '<';

      var homepage = '&homepage=' + data.homepage;
      var hideArticles = '&hide_articles=' + data.hideArticles;
      var topics = data.topics;

      var topicsFilter = '';
      if (angular.isObject(topics)) {
        angular.forEach(topics, function (topic, index) {
          topicsFilter += '&topics[' + index + ']=' + topic;
        });
      }

      // If we have more than one group then add "IN",
      // operator and breakdown the group IDs to separate filters.
      if (angular.isObject(data.group)) {
        var group_filter = '';
        angular.forEach(data.group, function (group, index) {
          group_filter += 'group[' + index + ']=' + group + '&';
        });

        return $http.get(
          DrupalSettings.getBasePath()
            + 'api/activity_stream?'
            + group_filter
            + '&sort=-timestamp&filter[timestamp][value]=' + timestamp
            + '&filter[timestamp][operator]="' + operator
            + '"&html=1'
            + homepage
            + hideArticles
            + topicsFilter
          , config
        );
      }

      return $http.get(DrupalSettings.getBasePath() + 'api/activity_stream?group='
      + data.group + '&sort=-timestamp&filter[timestamp][value]=' + timestamp
      + '&filter[timestamp][operator]="' + operator + '"&html=1' + homepage + hideArticles + topicsFilter, config);
    };
  });

'use strict';

/**
 * Provides the FileUpload service.
 *
 * @ngdoc service
 *
 * @name c4mApp.service:FileUpload
 *
 * @description Uploads file to drupal.
 */
angular.module('c4mApp')
  .service('FileUpload', function (DrupalSettings, $upload) {

    /**
     * Upload file.
     *
     * @param file
     *   The file to upload.
     *
     * @returns {*}
     *   The uplaoded file JSON.
     */
    this.upload = function (file) {
      return $upload.upload({
        url: DrupalSettings.getBasePath() + 'api/file-upload',
        method: 'POST',
        file: file,
        withCredentials:  true,
        headers: {
          "X-CSRF-Token": DrupalSettings.getCsrfToken()
        }
      });
    };
  });

'use strict';

/**
 * Provides the GoogleMap Service.
 *
 * @ngdoc service
 *
 * @name c4mApp.service:GoogleMap
 *
 * @description Sends request for address to google maps API.
 */
angular.module('c4mApp')
  .service('GoogleMap', function ($http) {

    this.getAddress = function (data, resource) {
      var url = 'http://maps.google.com/maps/api/geocode/json?address=';
      url += data.location.street ? data.location.street + ',' : '';
      url += data.location.city ? data.location.city : '';
      url += data.location.postal_code ? ' ' + data.location.postal_code : '';
      url += data.location.city || data.location.postal_code ? ',' : '';
      url += data.location.country_name ? ' ' + data.location.country_name : '';
      url += '&sensor=false';
      return $http.get(url);
    };
  });

'use strict';

/**
 * Provides the QuickPostService.
 *
 * @ngdoc service
 *
 * @name c4mApp.service:QuickPostService
 *
 * @description Imports the settings sent from drupal.
 */
angular.module('c4mApp')
  .service('QuickPostService', function ($rootScope, $http, DrupalSettings) {
    var self = this;

    /**
     * Set the default values to the scope.
     *
     * @param scope
     *  the scope object.
     *
     * @returns {*}
     *  Returns the scope object with the default values.
     */
    this.setDefaults = function (scope) {
      scope.documentName = '';

      scope.referenceValues = {};

      scope.errors = {};

      scope.serverSide = {
        status: 0,
        data: {}
      };

      scope.tagsQueryCache = [];

      // Date Calendar options.
      scope.minDate = new Date("January 1, 1970");

      scope.startOpened = false;

      scope.endOpened = false;

      scope.dateOptions = {
        formatYear: 'yyyy',
        startingDay: 1
      };

      scope.format = 'dd/MM/yyyy';

      // Time picker options.
      // Hour step.
      scope.hstep = 1;
      // Minute step.
      scope.mstep = 1;

      return scope;
    };

    /**
     * Prepare all the taxonomy-terms to be a tree object.
     *
     * @param scope
     *  The scope object.
     *
     * @returns {*}
     *  Returns the scope object with the prepared taxonomy-terms fields.
     */
    this.formatTermFieldsAsTree = function (scope) {
      angular.forEach(scope.referenceValues, function (data, field) {
        // Parent id.
        var parent = 0;
        var midParent = 0;

        scope[field] = {};
        angular.forEach(scope.referenceValues[field], function (fieldValue) {

          if (fieldValue.label.indexOf('-') == -1 && fieldValue.label.indexOf('--') == -1) {
            // This is parent term - 1 level.
            parent = fieldValue.id;
            scope[field][fieldValue.id] = {
              id: fieldValue.id,
              label: fieldValue.label,
              children: []
            };
          }
          else {
            if (fieldValue.label.indexOf('--') == -1) {
              // This is child term of 2 level.
              if (parent > 0) {
                midParent = fieldValue.id;
                scope[field][parent]['children'].push({
                  id: fieldValue.id,
                  label: fieldValue.label.replace('-',''),
                  children: []
                });
              }
            }
            else {
              // This is child term of 3 level.
              if (midParent > 0) {
                angular.forEach(scope[field][parent]['children'], function (value, key) {
                  if (value.id == midParent) {
                    scope[field][parent]['children'][key]['children'].push({
                      id: fieldValue.id,
                      label: fieldValue.label.replace('--','')
                    });
                  }
                });
              }
            }
          }
        });
      });

      return scope;
    };

    /**
     * Get matching tags.
     *
     * @param query
     *   The query string.
     * @param scope
     *   The scope object.
     */
    this.tagsQuery = function (query, scope) {
      var group = {id: scope.data.group};
      var url = DrupalSettings.getBasePath() + 'api/tags';
      var terms = {results: []};

      var lowerCaseTerm = query.term.toLowerCase();
      if (angular.isDefined(scope.tagsQueryCache[lowerCaseTerm])) {
        // Cache the tags result we got from the server,
        // to prevent re-query for the same ones.
        terms.results = scope.tagsQueryCache[lowerCaseTerm];
        query.callback(terms);
        return;
      }

      $http.get(url + '?autocomplete[string]=' + query.term + '&group=' + group.id)
        .success(function (data) {
          if (data.data.length == 0) {
            terms.results.push({
              text: query.term,
              id: query.term,
              isNew: true
            });
          }
          else {
            angular.forEach(data.data, function (label, id) {
              terms.results.push({
                text: label,
                id: id,
                isNew: false
              });
            });
            scope.tagsQueryCache[lowerCaseTerm] = terms;
          }

          query.callback(terms);
        });
    };

    /**
     * Called by the directive "bundle-select".
     *
     * Updates the bundle of the entity to send to the correct API url.
     *
     * @param resource
     *  The resource name.
     *  @param event
     *    The click event.
     *
     *  @returns string
     *    Returns a selected resource name.
     */
    this.updateResource = function (resource, event) {
      // Get element clicked in the event.
      var element = angular.element(event.srcElement);
      // Remove class "active" from all elements.
      angular.element(".bundle-select").removeClass("active");
      // Add class "active" to clicked element.
      element.addClass("active");
      // Update Bundle.
      return resource;
    };

    /**
     * Called by the directive "types".
     *
     * Updates the type of the selected resource.
     *
     * @param type
     *  The type.
     * @param field
     *  The name of the field.
     *  @param event
     *  The click event.
     */
    this.updateType = function (type, field, event) {
      // Get element clicked in the event.
      var element = angular.element(event.srcElement);
      // Remove class "active" from all elements.
      angular.element("." + field).removeClass("active");
      // Add class "active" to clicked element.
      element.addClass("active");
      // Update Bundle.
      return type;
    };

    /**
     * Find the taxonomy term name by its id.
     *
     * @param vocab
     *  Taxonomy vocabulary object.
     * @param termID
     *  Taxonomy term id.
     *
     * @returns string
     *  Returns the name of the taxonomy term.
     */
    this.findLabel = function (vocab, termID) {
      if (vocab[termID]) {
        return vocab[termID].label;
      }
      else {
        var termName = '';
        angular.forEach(vocab, function (value, key) {
          if (value.hasOwnProperty('children')) {
            angular.forEach(value.children, function (child, key) {
              var id = termID.toString();
              if (child.id == id) {
                termName = child.label;
              }
              else if (child.hasOwnProperty('children')) {
                angular.forEach(child.children, function (childChild, childKey) {
                  if (childChild.id == id) {
                    termName = childChild.label;
                  }
                });
              }
            });
          }
        });
        return termName;
      }
    };

    /**
     * Toggle the visibility of the popovers.
     *
     * @param name
     *   The name of the pop-over.
     * @param event
     *   The click event.
     * @param popups
     *   The scope object.
     */
    this.togglePopover = function (name, event, popups) {
      // Hide all the other pop-overs, Except the one the user clicked on.
      angular.forEach(popups, function (value, key) {
        if (name != key) {
          this[key] = 0;
        }
      }, popups);
      // Get the width of the element clicked in the event.
      var elemWidth = angular.element(event.currentTarget).outerWidth();
      // Toggle the visibility variable.
      popups[name] = popups[name] == 0 ? 1 : 0;
      // Move the popover to be at the end of the button.
      angular.element(".hidden-checkboxes").css('left', elemWidth);
    };
  });

'use strict';

/**
 * Service to clean and prepare the RESTful request object.
 *
 * @ngdoc service
 *
 * @name c4mApp.service:Request
 *
 * @description
 * # Cleans and prepares the RESTful request object.
 */
angular.module('c4mApp')
  .service('Request', function ($filter) {
    var Request = this;

    this.resourceFields = '';
    this.resource = '';

    /**
     * Prepare the request.
     *
     * @param data
     *   The data object to POST.
     *
     * @returns {*}
     *   The request object ready for RESTful.
     */
    this.prepare = function (data) {

      // Copy data, We shouldn't change the variables in the scope.
      var submitData = angular.copy(data);

      angular.forEach(submitData, function (values, field) {
        // Get the IDs of the selected references.
        // Prepare data to send to RESTful.
        if (Request.resourceFields[field] && field != 'tags' && field != 'notification') {
          var fieldType = Request.resourceFields[field].data.type;
          if (values && (fieldType == "entityreference" || fieldType == "taxonomy_term_reference")) {
            submitData[field] = [];
            angular.forEach(values, function (value, index) {
              if (value === true) {
                this[field].push(index);
              }
            }, submitData);
            // The group field should have one value.
            if (field == 'group' || field == 'related_document') {
              submitData[field] = values;
            }
          }
        }
      });

      // Assign tags.
      var tags = [];
      angular.forEach(submitData.tags, function (term, index) {
        if (term.isNew) {
          // New term.
          this[index] = {};
          this[index].label = term.id;
        }
        else {
          // Existing term.
          this[index] = term.id;
        }
      }, tags);

      var categories = submitData.categories;
      delete(submitData.categories);
      delete(submitData.tags);

      // Make sure 'categories' is defined.
      if (!categories) {
        categories = [];
      }

      submitData.categories = categories.concat(tags);

      return jQuery.param(submitData);
    };

    /**
     * Check for required fields.
     *
     * @param data
     *   The request data.
     * @param resource
     *   The entity resource.
     * @param resourceFields
     *   The fields information.
     *
     * @returns {*}
     *   The errors object.
     */
    this.checkRequired = function (data, resource, resourceFields) {
      var errors = {};
      var errorData = angular.copy(data);

      angular.forEach(errorData, function (values, field) {
        if (field == "tags" || field == 'notification') {
          return;
        }
        // Check that title has the right length.
        if (field == 'label' && values.length < 3) {
          this[field] = 1;
        }

        if (field == 'topic') {
          // Assume topics are always empty.
          var empty = true;
          // Check all terms whether any of them is checked by the user.
          angular.forEach(values, function (termIsChecked, tid) {
            // If we already found out topics are not empty we should skip.
            if (!empty) {
              return;
            }

            // When term is checked it will change the empty to be NOT empty.
            empty = !termIsChecked;
          });

          if (empty) {
            this[field] = 1;
          }
        }

        // Check required fields for validations, except for datetime field because we checked it earlier.
        var fieldRequired = resourceFields[field].data.required;
        if (fieldRequired && (!values) && field != "datetime") {
          this[field] = 1;
        }
      }, errors);

      return errors;
    };

    /**
     * Cleaning the submitted data from other resources fields.
     *
     * Because the RestFul will return an error if there's undefined fields.
     *
     * @param data
     *   The request data.
     * @param resourceFields
     *   The fields information.
     *
     * @returns {*}
     *  Object of the cleaned data.
     */
    this.cleanFields = function (data, resourceFields) {
      // Copy data, We shouldn't change the variables in the scope.
      var cleanData = angular.copy(data);
      angular.forEach(cleanData, function (values, field) {

        // Keep only the status field.
        if (!resourceFields[field] && field != "tags" && field != 'notification') {
          delete this[field];
        }

        // If there're related documents, add them.
        if (field == 'relatedDocuments') {
          this['related_document'] = values;
        }
      }, cleanData);

      return cleanData;
    };
  });
