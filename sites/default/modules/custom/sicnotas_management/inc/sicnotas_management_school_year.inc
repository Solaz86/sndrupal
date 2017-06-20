<?php

/**
 * Implements hook_form().
 */
function sicnotas_management_school_year_form($form, &$form_state) {
  $form['year'] = array(
    '#type' => 'textfield',
    '#title' => t('Create year')
  );

  $form['accept'] = array(
    '#type' => 'submit',
    '#value' => t('Accept'),
    '#name' => 'accept'
  );

  $form['confirmation_modal'] = modal_confirm_delete($form_state);  

  $form['table'] = array(
    '#type' => 'tableselect',
    '#header' => array('Year'),
    '#options' => get_year_table(),
    '#empty' => t('No campground to claim'),
    '#attributes' => array(
      'class' => array('table')
    )
  );

  $form['delete_selected'] = array(
    '#type' => 'submit',
    '#value' => t('Delete selected'),
    '#name' => 'show_confirm_delete',
    '#ajax' => array(
      'callback' => 'school_year_delete_callback'
    )
  );
  return $form;
}

/**
 * Implements hook_validate().
 */
function sicnotas_management_school_year_form_validate($form, &$form_state) {
  $filter = array_filter($form_state['values']['table']);
  $year = $form_state['values']['year'];
  if ($filter) {
    $year_id = db_select('sicnotas_management_school_year', 'smsy')
                  ->fields('smsy', array('id'))
                  ->condition('id', $filter, '=')
                  ->execute()->fetchField();
  }
  $year_exists = db_select('sicnotas_management_school_year', 'smsy')
                    ->fields('smsy', array('year'))
                    ->condition('year', $year)
                    ->execute()->fetchAll();
  if ($form_state['triggering_element']['#name'] == 'accept') {
    if (!empty($year_exists)) {
      form_set_error('year', t('the year already exist'));
    }
    else {
      $actual_year = date('Y') ;
      $next_years = $actual_year + 2;
      $last_year = $actual_year;
      if (!is_numeric($year)) {
        form_set_error('year', t('This field must be numeric'));
      };
      if ($year < ($last_year)) {
        form_set_error('year', t("The year can not be smaller than @last_year", array('@last_year' => $last_year)));
      };
      if ($year > $next_years) {
        form_set_error('year', t("The year can not be bigger than @next_year", array('@next_year' => $next_years)));
      }
    }
  }
  if ($form_state['triggering_element']['#name'] == 'confirm_delete'){
    $query = db_select('sicnotas_management_subjects_degree', 'smsd')
                ->fields('smsd', array('year_id'))
                ->condition('year_id', $year_id)
                ->countQuery()
                ->execute()->fetchField();
    if ($query) {
      form_set_error('year', t('Unable to delete, it is using it in subject degrees'));
    }
  }
}


/**
 * Implements hook_form_submit().
 */
function sicnotas_management_school_year_form_submit($form, &$form_state) {
  $table_name = str_replace('_form', '', $form_state['values']['form_id']);
  $subject_message = str_replace('form', '', str_replace('_', ' ', str_replace('sicnotas_management_', '', $table_name)));
  $form_state['storage']['delete'] = FALSE;
  $filter = array_filter($form_state['values']['table']);
  switch ($form_state['triggering_element']['#name']) {
    case 'accept':
      $year = $form_state['values']['year'];
      $record = array(
        'year' => $year,
      );
      db_insert($table_name)
        ->fields($record)
        ->execute();
      drupal_set_message(t("The $subject_message $year is successfully created"));
      break;

    case 'show_confirm_delete':
      if (!empty($filter)) {
        $new_state = $form_state['storage']['delete'] = TRUE;
        return  $new_state;
      }
      break;

    case 'confirm_delete':
      $subject_message = ucfirst($subject_message);
      if (!empty($filter)) {
        db_delete($table_name)
          ->condition('id', $filter, 'IN')
          ->execute();
      return drupal_set_message(t("$subject_message successfully deleted"));
      }
      break;
  }
}

function school_year_delete_callback($form, &$form_state){
  if (!empty($form_state['storage']['delete'])) {
    $commands = array();
    $commands[] = ajax_command_invoke('#myModal', 'modal', array('show'));
    return array(
      '#type' => 'ajax',
      '#commands' => $commands
    );
  }
}