<?php

/**
 * Implements hook_form().
 */
function sicnotas_management_competition_form($form, &$form_state) {
  $form['name'] = array(
  '#type' => 'textfield',
  '#title' => t('Create competition'),
  );

  $form['accept'] = array(
    '#type' => 'submit',
    '#value' => t('Accept'),
    '#name' => 'accept'
  );

  $form['confirmation_modal'] = modal_confirm_delete($form_state);

  $form['table'] = array(
    '#type' => 'tableselect',
    '#header' => array('Competition'),
    '#options' => get_competition_table(),
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
 * Implements hook_form_submit().
 */
function sicnotas_management_competition_form_submit($form, &$form_state) {
  $table_name = str_replace('_form', '', $form_state['values']['form_id']);
  $subject_message = str_replace('form', '', str_replace('_', ' ', str_replace('sicnotas_management_', '', $table_name)));
  $form_state['storage']['delete'] = FALSE;
  $filter = array_filter($form_state['values']['table']);
  switch ($form_state['triggering_element']['#name']) {
    case 'accept':
      $competition = $form_state['values']['name'];
      $record = array(
        'name' => $competition,
      );
      db_insert($table_name)
        ->fields($record)
        ->execute();
      drupal_set_message(t("The $subject_message $competition is successfully created"));
      break;

    case 'show_confirm_delete':
      if (!empty($filter)) {
        return  $form_state['storage']['delete'] = TRUE;
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
