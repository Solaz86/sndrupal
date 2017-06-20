<?php

/**
 * Available variables:
 * - $table: Tabla con los usuarios
 * - $forrm: Formulario de usuartios
 */

?>
<div class="formulario">
    <?php if (FALSE): ?>
        <form action="/carlos/pagina-custom" method="POST" id="carlos-form-form" accept-charset="UTF-8">
            <?php print drupal_render($form['form_build_id']) ?>
            <?php print drupal_render($form['form_id']) ?>
            <?php print drupal_render($form['form_token']) ?>

            <div class="left">
                <?php print drupal_render($form['age']) ?>
                <?php print drupal_render($form['name']) ?>
            </div>
            <?php print drupal_render($form['lastname']) ?>
            <?php print drupal_render($form['opsex']) ?>
            <?php print drupal_render($form['tel']) ?>
            <?php print drupal_render($form['create']) ?>
            <?php print drupal_render($form['update']) ?>
            <?php print drupal_render($form['volver']) ?>
        </form>
    <?php endif; ?>
    <?php print $form ?>
</div>


<div class="maintable">
    <?php print $table ?>
</div>

<table>
    <thead>
        <tr>
            <?php foreach ($tabla['header'] as $columnName): ?>
                <th><?php print $columnName ?></th>
            <?php endforeach; ?>
        </tr>
    </thead>
    <tbody>
        <?php foreach ($tabla['rows'] as $row): ?>
            <tr>
                <?php foreach ($row as $rowName): ?>
                    <td><?php print $rowName ?></td>
                <?php endforeach; ?>
            </tr>
        <?php endforeach; ?>
    </tbody>
</table>