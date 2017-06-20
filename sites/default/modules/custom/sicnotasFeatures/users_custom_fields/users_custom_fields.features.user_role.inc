<?php
/**
 * @file
 * users_custom_fields.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function users_custom_fields_user_default_roles() {
  $roles = array();

  // Exported role: School administrator.
  $roles['School administrator'] = array(
    'name' => 'School administrator',
    'weight' => 3,
  );

  // Exported role: Student.
  $roles['Student'] = array(
    'name' => 'Student',
    'weight' => 5,
  );

  // Exported role: Teacher.
  $roles['Teacher'] = array(
    'name' => 'Teacher',
    'weight' => 4,
  );

  return $roles;
}
