<?php

/**
* Clase filtro para ordenar por numero de vistas
*/
class carlos_form_handler_filter_most_viewed extends views_handler_filter
{
  function admin_summary() {}
  function operator_form(&$form, &$form_state) {}
  function can_expose() {
    return FALSE;
  }

  /**
  * En el query agregamos una nueva expresión.
  */
  function query() {
    // dpm($this, 'en el handler');
    $most_viewed = get_most_viewed_nodes();
    $most_views_nids = implode(',', $most_viewed); // se convierte a string por medio de la funcion implode para poder hacer el query add_where_expression

    // Agregamos la expresión al query.
    $table = $this->query->ensure_table('node', $this->relationship); 
    $this->query->add_where_expression(1, $table . ".nid  IN ({$most_views_nids})");
    // Ordenamos los resultados en el orden de los NIDS.
    $this->query->orderby[0]['field'] = "FIELD(node.nid, $most_views_nids)";
    $this->query->orderby[0]['direction'] = '';
  }

  
}