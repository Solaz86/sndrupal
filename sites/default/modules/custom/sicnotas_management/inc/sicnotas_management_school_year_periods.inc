<?php

// /**
//  * Implements hook_form().
//  */
// function sicnotas_management_school_year_periods_form($form, &$form_state) {
//   $form['year_periods_quantity'] = array(
//     '#title' => t('Year periods quantity'),
//     '#description' => t('How many periods'),
//     '#type' => 'select',
//     '#options' => array(1,2,3,4,5,6,7,8,9,10)
//   );
//   $form['year_id'] = array(
//     '#title' => t('Year'),
//     '#description' => t('Select the year'),
//     '#type' => 'select',
//     '#options' => years_options()
//   );
//   $form['accept'] = array(
//     '#type' => 'submit',
//     '#value' => t('Accept')
//   );

//   // $form['confirmation_modal'] = modal_confirm_delete($form_state);

//   // $form['table'] = array(
//   //   '#type' => 'tableselect',
//   //   '#header' => array('Year'),
//   //   '#options' => year_table(),
//   //   '#empty' => t('No campground to claim'),
//   // );

//   // $form['delete_selected'] = array(
//   //   '#type' => 'submit',
//   //   '#value' => t('Delete selected'),
//   //   '#name' => 'show_confirm_delete',
//   //   '#ajax' => array(
//   //     'callback' => 'school_year_delete_callback'
//   //   )
//   // );
//   return $form;
// }


// /**
//  * Implements hook_views_form_validate().
//  */
// function sicnotas_management_school_year_periods_form_validate($form, &$form_state) {
//   if ($form_state['triggering_element']['#name'] == 'accept') {
//     $year = $form_state['values']['year'];
//     $actual_year = date('Y') ;
//     $next_years = $actual_year + 2;
//     $last_year = $actual_year - 2;
//     if (!is_numeric($year)) {
//       form_set_error('year', t('This field must be numeric'));
//     };
//     if ($year < ($last_year)) {
//       form_set_error('year', t("The year can not be smaller than @last_year", array('@last_year' => $last_year)));
//     };
//     if ($year > $next_years) {
//       form_set_error('year', t("The year can not be bigger than @next_year", array('@next_year' => $next_years)));
//     }
//   }
// }


// /**
//  * Implements hook_node_submit().
//  */
// function sicnotas_management_school_year_periods_form_submit($form, &$form_state) {  
//   $table_name = str_replace('_form', '', $form_state['values']['form_id']);
//   $subject_message = str_replace('form', '', str_replace('_', ' ', str_replace('sicnotas_management_', '', $table_name)));
//   $form_state['storage']['delete'] = FALSE;
//   $filter = array_filter($form_state['values']['table']);

//   switch ($form_state['triggering_element']['#name']) {
//     case 'accept':
//       $year = $form_state['values']['year'];
//       $record = array(
//         'year' => $year,
//       );
//       db_insert($table_name)
//         ->fields($record)
//         ->execute();
//       drupal_set_message(t("The $subject_message $year is successfully created"));
//       break;

//     case 'show_confirm_delete':
//       if (!empty($filter)) {
//         return  $form_state['storage']['delete'] = TRUE;
//       }
//       break;

//     case 'confirm_delete':
//       $subject_message = ucfirst($subject_message);
//       if (!empty($filter)) {
//         db_delete($table_name)
//           ->condition('id', $filter, 'IN')
//           ->execute();
//       return drupal_set_message(t("$subject_message successfully deleted"));
//       }
//       break;
//   }
// }

// function school_year_delete_callback($form, &$form_state){
//   if (!empty($form_state['storage']['delete'])) {
//     $commands = array();
//     $commands[] = ajax_command_invoke('#myModal', 'modal', array('show'));
//     return array(
//       '#type' => 'ajax',
//       '#commands' => $commands
//     );
//   }
// }
//crear form in line para elegir inicion y finalizacion de cada periodo