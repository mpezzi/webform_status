<div class="webform-status webform-status-<?php print $node->nid; ?>">
  <table class="webform-status webform-status-<?php print $node->nid; ?>">
    <thead>
      <tr>
        <td width="15%"></td>
        <?php foreach ( $reports as $report ): ?>
          <th width="<?php print floor( 85 / count($reports) ); ?>%"><?php print $report['#title']; ?></th>
        <?php endforeach; ?>
      </tr>
    </thead>
    <tbody>
      <tr>
        <th><?php print $node->title; ?></th>
        <?php foreach ( $reports as $report ): ?>
          <td><?php print $report['#value']; ?></td>
        <?php endforeach; ?>
      </tr>
    </tbody>
  </table>
</div>
