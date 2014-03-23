<?php

/**
 * @file
 * Functions deriving fasta files for objects.
 */
 
/**
 * Copies the Fasta file to the file system.
 *
 * @param AbstractObject $object
 *   An AbstractObject representing an object within Fedora.
 *
 * @return array|stdClass
 *   FALSE when the object doesn't have the OBJ, an array otherwise.
 *
 *	@author Quintin Dawson
 */
function islandora_bioinformatics_genesequence_copy_fasta_datastream(AbstractObject $object) {
  
  $mime_detect = new MimeDetect();
  if (!isset($object['FASTA'])) {
    return FALSE;
  }
  $ext = $mime_detect->getExtension($object['FASTA']->mimeType);
  $file_name = str_replace(':', '-', $object->id);

  // Create a file object we can save.
  //$file_uri = file_create_filename("{$file_name}FASTA.{$ext}", 'temporary://');
  $file_uri = file_create_filename("{$file_name}FASTA.{$ext}", 'public://fasta');
  $file = new stdClass();
  $file->uri = $file_uri;
  $file->filename = $file_name;
  $file->filemime = $object['FASTA']->mimeType;
 
  
  $file->status = 0;
  $object['FASTA']->getContent($file_uri);
  $original_file = file_save($file);
  
  //testing
  $file_copy($original_file, 'public://fasta' . $file->file_name . $file->$ext);
  
  return array(
    'file' => $original_file,
    'extension' => $ext,
    'filename' => $file_name,
  );
  
}