<?php

/**
 * Implements hook_views_data_alter().
 */
function carlos_form_views_data_alter(&$data) {
  // $data['node']['title_count']['title'] = 'Counter Views';
  // $data['node']['title_count']['help'] = 'Count node views.';
  // $data['node']['title_count']['filter']['handler'] = 'carlos_form_handler_filter_most_viewed';

  $data['node']['count_views_custom'] = array(
    'title' => t('Most viewed'),
    'help' => t('Most viewed'),
    'group' => 'Carlos custom filters',
    'filter' => array(
      'handler' => 'carlos_form_handler_filter_most_viewed',
    ),
  );
}