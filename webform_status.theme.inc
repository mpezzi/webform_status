<?php

/**
 * Add required CSS/JavaScript files.
 */
function webform_status_add_files() {
  static $added;
  
  if ( !isset($added) ) {
    $module_path = drupal_get_path('module', 'webform_status');
    
    drupal_add_css($module_path .'/webform_status.css');
    drupal_add_css($module_path .'/js/visualize/visualize.css');
    drupal_add_css($module_path .'/js/visualize/visualize-dark.css');
    drupal_add_js($module_path .'/js/visualize/excanvas.js');
    drupal_add_js($module_path .'/js/visualize/visualize.js');
    drupal_add_js($module_path .'/webform_status.js');
    $added = TRUE;
  }
}

/**
 * Implementation of template_preprocess_webform_status().
 */
function template_preprocess_webform_status(&$vars, $hook) {
  webform_status_add_files();
  
  $options = array(
    'type' => 'bar',
    'width' => 600,
    'height' => 200,
    'barMargin' => 10,
  );
  
  drupal_add_js(array('webform_status_visualize' => array('table.webform-status-'. $vars['node']->nid => $options)), 'setting');
}

/**
 * Implementation of template_preprocess_webform_status().
 */
function template_preprocess_webform_status_all(&$vars, $hook) {
  webform_status_add_files();
  
  $options = array(
    'type' => 'bar',
    'width' => 900,
    'height' => 200,
    'barMargin' => 10,
  );
  
  drupal_add_js(array('webform_status_visualize' => array('table.webform-status-all' => $options)), 'setting');
}
