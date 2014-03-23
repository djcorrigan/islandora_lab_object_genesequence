<?php

/**
 * @file
 * Functions deriving fasta files for objects.
 */

 /**
 * Creates the fasta file derivative for a fasta.
 *
 * @param AbstractObject $object
 *   An AbstractObject representing a Fedora object.
 * @param bool $force
 *   Whether derivative generation is being forced or not.
 *
 * @return array
 *   An array describing the outcome of the fasta creation.
 *
 * @see hook_islandora_derivative()
 */

 
/**
 * Copies the OBJ to the file system.
 *
 * @param AbstractObject $object
 *   An AbstractObject representing an object within Fedora.
 *
 * @return array|stdClass
 *   FALSE when the object doesn't have the OBJ, an array otherwise.
 *
 *	@author Quintin Dawson
 */
function islandora_basic_image_copy_obj_datastream(AbstractObject $object) {
  $mime_detect = new MimeDetect();
  if (!isset($object['FASTA'])) {
    return FALSE;
  }
  $ext = $mime_detect->getExtension($object['FASTA']->mimeType);
  $file_name = str_replace(':', '-', $object->id);

  // Create a file object we can save.
  $file_uri = file_create_filename("{$file_name}FASTA.{$ext}", 'temporary://');
  $file = new stdClass();
  $file->uri = $file_uri;
  $file->filename = $file_name;
  $file->filemime = $object['FASTA']->mimeType;
  // Temporary.
  $file->status = 0;
  $object['FASTA']->getContent($file_uri);
  $original_file = file_save($file);
  return array(
    'file' => $original_file,
    'extension' => $ext,
    'filename' => $file_name,
  );
}