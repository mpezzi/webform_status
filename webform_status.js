/**
 * Implementation of Drupal JavaScript Behaviors.
 */
Drupal.behaviors.webform_status_visualize = function() {
  jQuery.each(Drupal.settings.webform_status_visualize, function(selector, options){
    $(selector).visualize(options);
  });
};