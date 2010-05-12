<div class="webform-status-all">
  <table class="webform-status-all">
    <thead>
      <tr>
        <td width="15%"></td>
        <?php foreach ( $reports[0] as $report ): ?>
          <th width="<?php print floor( 85 / count($reports) ); ?>%"><?php print $report['#title']; ?></th>
        <?php endforeach; ?>
      </tr>
    </thead>
    <tbody>
      <?php foreach ( $nodes as $key => $node ): ?>
      <tr>
        <th><?php print l($node->title, 'node/'. $node->nid); ?></th>
        <?php foreach ( $reports[$key] as $report ): ?>
          <td><?php print $report['#value']; ?></td>
        <?php endforeach; ?>
      </tr>
      <?php endforeach; ?>
    </tbody>
  </table>
</div>
