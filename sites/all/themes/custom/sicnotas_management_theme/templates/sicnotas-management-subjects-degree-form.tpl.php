
<h3>Año <?php print $form['year']['#value']; ?> </h3>
<table id="example" class="display" width="100%" cellspacing="0">
  <thead>
    <tr>
      <th>Cursos</th>
      <?php
        $subjects = $form['subject_id']['#value'];
        if(is_array($subjects) && count($subjects)>0) :
          foreach($subjects as $key => $value) :
            $materia = reset($value);
      ?>
            <th class="td-center"><?php print $materia; ?></th>
          <?php endforeach;?>
        <?php endif; ?>
      <th></th>
    </tr>
  </thead>
  <tfoot>
    <tr>
      <th>Cursos</th>
      <?php
        $subjects = $form['subject_id']['#value'];
        if(is_array($subjects) && count($subjects)>0) :
          foreach($subjects as $key => $value) :
            $materia = reset($value);
      ?>
            <th class="td-center"><?php print $materia; ?></th>
          <?php endforeach;?>
        <?php endif; ?>
      <th></th>
    </tr>
  </tfoot>
  <tbody>
      <?php
        $degrees = $form['degrees']['#value'];
        $checkboxes = &$form['check'];
        if(is_array($degrees) && count($degrees)>0) :
          foreach($degrees as $key => $degree) :
            $degreeCheckbox = &$checkboxes[$degree->id];
      ?>
             <tr>
              <td><p class="td-center"><?php print $degree->name; ?></p></td>
              <?php foreach ($degreeCheckbox as $checkId => &$checkbox) : 
                if (isset($checkbox['#type']) && $checkbox['#type'] == 'checkbox') : ?>
                 <td><?php print render($checkbox); ?></td>
                <?php endif;?>
              <?php endforeach;?>
          <?php endforeach;?>
        <?php endif; ?>
              </tr>
            
  </tbody>
</table>
 <?php 
 print drupal_render_children($form); ?>

