<?php

/**
 * @file
 * Suggestion class which contains both the original search key and the
 * suggested replacement.
 */
class SearchApiSpellcheckSuggestion {
  public $original;
  public $suggestion;

  /**
   * Constructor.
   *
   * @param string $original
   *   Word, phrase or sentance which could be improved.
   *
   * @param string $suggestion
   *   Suggested replacement for the $original.
   */
  public function __construct($original, $suggestion) {
    $this->original = $original;
    $this->suggestion = $suggestion;
  }

  /**
   * Apply this suggestion to the string passed as parameter
   *
   * @param $string
   *   A string to transform.
   *
   * @return string
   *   The input string with this suggestion applied on it. The input string
   *   won't necessarily be changed.
   *
   */
  public function apply($string) {
    // Use a regular expression to replace only full words and not part of a
    // word.
    return preg_replace(
      '/\b' . preg_quote($this->original, '/') . '\b/iu',
      $this->suggestion,
      $string);
  }
}
