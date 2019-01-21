<?php

/**
 * @file
 * Prints out the list of suggested projects.
 */
?>

<?php
$classes = '';
if ($display_more_button) {
  $classes = ' pane--more';
}
?>

<div class="sidebarblock suggested-projects<?php print $classes; ?>">
  <h2 class="sidebarblock__title"><?php print t('Suggested Projects') ?></h2>
  <?php print $projects ?>
  <?php if ($display_more_button): ?>
  <div class="sidebarblock__viewmore">
    <a href="<?php print $link; ?>"><?php print t('See more') ?> <i class="fa fa-chevron-right"></i></a>
  </div>
  <?php endif; ?>
</div>
