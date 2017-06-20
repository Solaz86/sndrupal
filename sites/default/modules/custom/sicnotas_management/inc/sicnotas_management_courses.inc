<?php

/**
 * Implements hook_form().
 */
function sicnotas_management_courses_form($form, &$form_state) {

  $form['degree_id'] = array(
    '#title' => t('Degree'),
    '#description' => t('Select the degree'),
    '#type' => 'select',
    '#options' => degrees_options()
  );

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Create course')
  );

  $form['confirmation_modal'] = modal_confirm_delete($form_state);

  $form['accept'] = array(
    '#type' => 'submit',
    '#value' => t('Accept'),
    '#name' => 'accept'
  );

// tabla con 2 header
  $options = array();
  foreach (get_courses_degree_table() as $key => $value) {
    $key_option = $value->course_id;
    $options[$key_option] = array(
      $value->degree_name,
      $value->course_name
    );
  }
  $form['table'] = array(
    '#type' => 'tableselect',
    '#header' => array(t('Degree'), t('Course')),
    '#options' => $options,
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
      'callback' => 'delete_callback'
    )
  );
  return $form;
}

/**
 * Implements hook_validate().
 */
function sicnotas_management_courses_form_validate($form, &$form_state) {
  if ($form_state['triggering_element']['#name'] == 'accept') {
    $course = $form_state['values']['name'];
    $degree_id = $form_state['values']['degree_id'];
    $query = db_select('sicnotas_management_courses', 'smc');
    $query->join('sicnotas_management_degrees', 'smd', 'smc.degree_id = smd.id');
    $query->fields('smc')
          ->condition('smc.name', $course)
          ->condition('smc.degree_id', $degree_id)
          ->countQuery();
    $result = $query->execute()->fetchField();
    if ($result) {
      form_set_error(t('name'), t('this course already exist'));
    }
  }
}

/**
 * Implements hook_form_submit().
 */
function sicnotas_management_courses_form_submit($form, &$form_state) {
  $table_name = str_replace('_form', '', $form_state['values']['form_id']);
  $subject_message = str_replace('form', '', str_replace('_', ' ', str_replace('sicnotas_management_', '', $table_name)));
  $form_state['storage']['delete'] = FALSE;
  $filter = array_filter($form_state['values']['table']);
  switch ($form_state['triggering_element']['#name']) {
    case 'accept':
      $record = array(
        'name' => $form_state['values']['name'],
        'degree_id' => $form_state['values']['degree_id'],
      );
      db_insert('sicnotas_management_courses')
      ->fields($record)
      ->execute();
      drupal_set_message(t('Degree successfully updated'));
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

function delete_callback($form, &$form_state){
  if (!empty($form_state['storage']['delete'])) {
    $commands = array();
    $commands[] = ajax_command_invoke('.modal-confirm-delete', 'modal', array('show'));
    return array(
      '#type' => 'ajax',
      '#commands' => $commands
    );
  }
}