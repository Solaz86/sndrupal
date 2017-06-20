<?php

/**
 * Implements hook_form().
 */
function sicnotas_management_subjects_form($form, &$form_state) {

  $form['name'] = array(
  '#type' => 'textfield',
  '#title' => t('Create subject')
  );

  $form['accept'] = array(
    '#type' => 'submit',
    '#value' => t('Accept'),
    '#name' => 'accept'
  );

  $form['confirmation_modal'] = modal_confirm_delete($form_state);

  $form['table'] = array(
    '#type' => 'tableselect',
    '#header' => array('Subjects'),
    '#options' => get_subjects_table(),
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
function sicnotas_management_subjects_form_validate($form, &$form_state) {
  $filter = array_filter($form_state['values']['table']);

  if ($form_state['triggering_element']['#name'] == 'accept') {
    if (empty($form_state['values']['name'])) {
      form_set_error('name', t('This field can not be blank'));
    };
  }

  if ($form_state['triggering_element']['#name'] == 'confirm_delete'){
    $query = db_select('sicnotas_management_subjects_degree', 'smsd')
                ->fields('smsd', array('subject_id'))
                ->condition('subject_id', $filter)
                ->countQuery()
                ->execute()->fetchField();
    if ($query) {
      form_set_error('name', t('Unable to delete, it is using it in Subject of each degree registration form'));
    }
  }
}


/**
 * Implements hook_form_submit().
 */
function sicnotas_management_subjects_form_submit($form, &$form_state) {
  $table_name = str_replace('_form', '', $form_state['values']['form_id']);
  $subject_message = str_replace('form', '', str_replace('_', ' ', str_replace('sicnotas_management_', '', $table_name)));
  $form_state['storage']['delete'] = FALSE;
  $filter = array_filter($form_state['values']['table']);
  switch ($form_state['triggering_element']['#name']) {
    case 'accept':
      $record = array(
        'name' => $form_state['values']['name'],
      );
      db_insert($table_name)
        ->fields($record)
        ->execute();
      drupal_set_message(t("The $subject_message is successfully created"));
      break;

    case 'show_confirm_delete':
      if (!empty($filter)) {
        return  $form_state['storage']['delete'] = TRUE;
      }
      break;
//si hay datos en tablas que se alimentan de esta no deberia poderse eliminar 
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
