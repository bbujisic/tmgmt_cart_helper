<?php

function tmgmt_cart_helper_bulk_translate_form() {
  $form['import'] = array(
    '#title' => t('URLs'),
    '#type' => 'textarea',
    '#description' => t('Please type or paste a list of node URLs into the test area. One URL per line. You can use both aliases (e.g. www.example.com/about-us) and internal urls (e.g. www.example.com/node/123).'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'submit',
  );

  return ($form);
}

function tmgmt_cart_helper_bulk_translate_form_submit($form, &$form_state) {
  global $base_url;
  $items = explode("\n", $form_state['values']['import']);

  $failed_paths = array();
  $nids = array();
  foreach ($items as $item) {
    $path = str_replace($base_url, '', $item);
    $path = trim($path, '/');
    $path = str_replace('en-us/', '', $path);
    $path = trim($path);
    $path = drupal_get_normal_path($path);

    $args = explode('/', $path);



    if ($args[0] == 'node' && is_numeric($args[1]) && !isset($args[2])) {
      $nids[$args[1]] = $args[1];
    } else {
      $failed_paths[] = check_plain($item);
    }
  }


  if (count($failed_paths) > 0) {
    drupal_set_message(t('Following items are not valid node URLs: !urls', array('!urls' => theme('item_list', array('items' => $failed_paths)))), 'warning');
  }

  if(count($nids) > 0) {
    tmgmt_cart_helper_add_nodes($nids);
  }
}