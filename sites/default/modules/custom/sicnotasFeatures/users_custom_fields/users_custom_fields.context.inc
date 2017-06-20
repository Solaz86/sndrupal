<?php
/**
 * @file
 * users_custom_fields.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function users_custom_fields_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'content_register';
  $context->description = 'contenidos de pagina de registro de usuarios';
  $context->tag = 'usuarios';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'staff-register' => 'staff-register',
      ),
    ),
    'user' => array(
      'values' => array(
        'School administrator' => 'School administrator',
        'administrator' => 'administrator',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-staff_data-block' => array(
          'module' => 'views',
          'delta' => 'staff_data-block',
          'region' => 'footer_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('contenidos de pagina de registro de usuarios');
  t('usuarios');
  $export['content_register'] = $context;

  return $export;
}
