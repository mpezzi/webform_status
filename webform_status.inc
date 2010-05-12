<?php

/**
 * Implementation of hook_webform_status_report().
 */
function webform_status_webform_status_report($node) {
  $email = _webform_status_get_component($node, 'email');
  $optin = _webform_status_get_component($node, 'receive_information');
  $optin_client = _webform_status_get_component($node, 'available_list');
  
  $vars = array('@type' => strtolower(node_get_types('name', $node)));
  
  return array(
    'total' => array(
      '#title' => t('Total'),
      '#description' => t('Total number of entries to the @type', $vars),
      '#sql' => "SELECT COUNT(*) FROM {webform_submissions} WHERE nid = ". $node->nid,
    ),
    'unique' => array(
      '#title' => t('Unique'),
      '#description' => t('Unique number of entires to the @type', $vars),
      '#sql' => "SELECT COUNT(DISTINCT d.data) FROM {webform_submissions} AS s INNER JOIN {webform_submitted_data} AS d ON s.sid = d.sid AND d.cid = ". $email->cid ." WHERE s.nid = ". $node->nid,
      '#components' => array('email'),
    ),
    'unique_optin' => array(
      '#title' => t('Unique Optin'),
      '#description' => t('Number of unique entries that wish to be contacted by the @type creators.', $vars),
      '#sql' => "SELECT COUNT(DISTINCT u.data) FROM {webform_submissions} AS s INNER JOIN {webform_submitted_data} AS d ON s.sid = d.sid AND d.cid = ". $optin->cid ." INNER JOIN {webform_submitted_data} AS u ON s.sid = u.sid AND u.cid = ". $email->cid ." WHERE s.nid = ". $node->nid ." AND d.data LIKE '%Yes%'",
      '#components' => array('email', 'receive_information'),
    ),
    'unique_client_optin' => array(
      '#title' => t('Unique Client Optin'),
      '#description' => t('Number of unique entries that wish to be contacted by the @type sponsor.', $vars),
      '#sql' => "SELECT COUNT(DISTINCT u.data) FROM {webform_submissions} AS s INNER JOIN {webform_submitted_data} AS d ON s.sid = d.sid AND d.cid = ". $optin_client->cid ." INNER JOIN {webform_submitted_data} AS u ON s.sid = u.sid AND u.cid = ". $email->cid ." WHERE s.nid = ". $node->nid ." AND d.data LIKE '%Yes%'",
      '#components' => array('email', 'available_list'),
    ),
  );
}

/**
 * Build a report for the current node.
 */
function _webform_status_build_report($node) {
  $hooks = module_invoke_all('webform_status_report', $node);
  
  foreach ( $hooks as $name => &$hook ) {
    if ( !isset($hook['#components']) ) {
      $hook['#components'] = array();
    }
    
    if ( isset($hook['#sql']) && _webform_status_has_components($node, $hook['#components']) ) {
      $value = db_result(db_query($hook['#sql']));
      $hook['#value'] = !empty($value) ? $value : 0;
    } else {
      $hook['#value'] = 0;
    }
  }
  
  return $hooks;
}

/**
 * Return a node webform component.
 */
function _webform_status_get_component($node, $form_key) {
  $components = _webform_status_get_components($node);
  
  foreach ( $components as $component ) {
    if ( $component->form_key == $form_key ) {
      return $component;
    }
  }
  
  return FALSE;
}

/**
 * Return an array of webform components.
 */
function _webform_status_get_components($node) {
  static $components;
  
  if ( !isset($components) ) {
    $components = array();
  }
  
  // Check if there is a cached version of the node components.
  if ( !isset($components[$node->nid]) ) {
    // Get components that are associated with the node.
    $result = db_query("SELECT * FROM {webform_component} WHERE nid = %d ORDER BY cid", $node->nid);

    while ( $component = db_fetch_object($result) ) {
      $components[$node->nid][] = $component;
    }
  }
  
  return $components[$node->nid];
}

/**
 * Determine if a node has certain components.
 */
function _webform_status_has_components($node, $components = array()) {
  $has_components = TRUE;
  if ( count($components) > 0 ) {
    foreach ( $components as $component ) {
      if ( !_webform_status_get_component($node, $component) ) {
        $has_components = FALSE;
      }
    }
  }
  
  return $has_components;
}
