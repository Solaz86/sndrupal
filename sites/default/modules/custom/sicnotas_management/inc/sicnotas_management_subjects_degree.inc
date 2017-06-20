<?php

/**
 * Implements hook_form().
 */
function sicnotas_management_subjects_degree_form($form, &$form_state, $year) {

  $year_id = db_select('sicnotas_management_school_year', 'smsy')
              ->fields('smsy', array('id'))
              ->condition('year', $year, '=')
              ->execute()->fetchField();


  $course_name = array();
  foreach (get_courses_degree_table() as $key => $value) {
    $course_name[][] = $value->degree_name;
  }

  $degrees = get_degrees();
  $form['degrees'] = array(
    '#type' => 'item',
    '#value' => $degrees
  );

  $form['subject_id'] = array(
    '#type' => 'item',
    '#value' => get_subjects_table()
  );

  $form['year'] = array(
    '#name' => 'year',
    '#type' => 'hidden',
    '#value' => $year
  );

  // Recorremos los cursos

  $form['check'] = array();
  foreach ($degrees as $key => $value) {
    $degree_id = $value->id;
    $form['check'][$degree_id]= array(
      '#tree' => TRUE
      );
    // Recorremos las materias
    foreach (subjects_options() as $subject_id => $subject) {
      $status = db_select('sicnotas_management_subjects_degree', 'smsd')
                  ->fields('smsd')
                  ->condition('year_id', $year_id)
                  ->condition('subject_id', $subject_id)
                  ->condition('degree_id', $degree_id)
                  ->countQuery()
                  ->execute()->fetchField();
      $id_check = $degree_id . "-" . $subject_id;
        $form['check'][$degree_id][$id_check] = array(
          '#type' => 'checkbox',
          '#default_value' => $status ? TRUE : FALSE
        );
    }
  }

  $form['accept'] = array(
    '#type' => 'submit',
    '#value' => t('Accept'),
    '#name' => 'acceptttt',
  );
  return $form;
}

/**
 * Implements hook_node_submit().
 */
function sicnotas_management_subjects_degree_form_submit($form, &$form_state) {

  $year = $form_state['values']['year'];
  $year_id = db_select('sicnotas_management_school_year', 'smsy')
              ->fields('smsy', array('id'))
              ->condition('year', $year, '=')
              ->execute()->fetchField();

  $trueChecked = array();
  foreach ($form_state['values'] as $content => $data) {
    if (is_numeric($content)) {
      $trueChecked[] = array_filter($data);
      $contentArray[] = $data;
    }
  }
  foreach ($contentArray as $key1 => $value1) {
    foreach ($value1 as $ke => $statusCheck) {
      list($tableDegreeId, $tableSubjectId) = explode('-', $ke);
  //si existe y esta chequeado en la tabla no hace nada
      $match_count = db_select('sicnotas_management_subjects_degree', 'smsd')
                        ->fields('smsd')
                        ->condition('year_id', $year_id)
                        ->condition('subject_id', $tableSubjectId)
                        ->condition('degree_id', $tableDegreeId)
                        ->countQuery()
                        ->execute()->fetchField();
// si no existe y esta chequeado lo guarda
      if ($statusCheck && !$match_count) {
        $record = array(
          'year_id' => $year_id,
          'degree_id' => $tableDegreeId,
          'subject_id' => $tableSubjectId,
        );
        db_insert('sicnotas_management_subjects_degree')
          ->fields($record)
          ->execute();
        drupal_set_message(t('register successfull updated'));
// si existe y no esta chequeado lo elimina
      }elseif (!$statusCheck && $match_count) {
        db_delete('sicnotas_management_subjects_degree')
            ->condition('year_id', $year_id)
            ->condition('degree_id', $tableDegreeId)
            ->condition('subject_id', $tableSubjectId)
            ->execute();
        drupal_set_message(t('register successfull deleted'));
      }
    }
  }
}
