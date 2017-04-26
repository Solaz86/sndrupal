
<div id="header">
  <?php print render($page['header']); ?>
  <img src="/<?php print $directory;?>/images/logo.png" alt="<?php print $site_name;?>" height="80" width="150" />
</div>

<div id="wrapper">
  <div id="content">
    <?php print render($page['content']); ?>
    <?php print render($logo); ?>
  </div>
  <div id="side-right">
    <?php if ($page['right']): ?>    
    <?php print render($page['right']); ?>
  <?php endif; ?>
  </div>
</div>

<div id="footer">
  <?php if ($page['footer']): ?>    
    <?php print render($page['footer']); ?>
  <?php endif; ?>
</div>



