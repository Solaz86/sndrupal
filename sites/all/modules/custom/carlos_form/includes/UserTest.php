<?php

/**
* Clase de usuarios
*/
class UserTest
{

  protected $user;
  protected $userW;
  
  /**
   * Construct funcrion
   */
  function __construct ($user_id)
  {
    $this->user = user_load($user_id);
    $this->userW = entity_metadata_wrapper('user', $this->user);
  }

  /**
   * Gets the wrapper.
   *
   * @return     object  The wrapper.
   */
  public function getWrapper() {
    return $this->userW;
  }

  /**
   * Gets the user.
   *
   * @return     object  The user.
   */
  public function getUser () {
    return $this->user;
  }

  /**
   * Gets the roles.
   *
   * @return     array  The roles.
   */
  public function getRoles () {
    return $this->user->roles;
  }

  /**
   * Gets the user identifier.
   *
   * @return     int  The user identifier.
   */
  public function getUserId(){
    return $this->user->uid;
  }

  /**
   * Gets the user name.
   *
   * @return     string  The user name.
   */
  public function getUserName () {
    return $this->user->name;

  }

  /**
   * Gets the user last name.
   *
   * @return     string  The user last name.
   */
  public function getUserLastName(){
    return $this->userW->field_apellido->value();
  }

  /**
   * Gets the user tel.
   *
   * @return     string  The user tel.
   */
  public function getUserTel(){
    return $this->userW->field_telefono->value();
  }

  /**
   * Gets the user age.
   *
   * @return     string  The user age.
   */
  public function getUserAge(){
    return $this->userW->field_edad->value();
  }

  /**
   * Gets the user opsex.
   *
   * @return     string  The user opsex.
   */
  public function getUserOpsex(){
    return $this->userW->field_genero->value();
  }

  /**
   * Sets the user name.
   *
   * @param      string  $name   The name
   */
  public function setUserName ($name) {
    $this->userW->name->set($name);
  }

  /**
   * Sets the user last name.
   *
   * @param      string  $lastName  The last name
   */
  public function setUserLastName ($lastName) {
    $this->userW->field_apellido->set($lastName);
  }

  /**
   * Sets the user tel.
   *
   * @param      string  $tel    The tel
   */
  public function setUserTel ($tel) {
    $this->userW->field_telefono->set($tel);
  }

  /**
   * Sets the user age.
   *
   * @param      string  $age    The age
   */
  public function setUserAge ($age) {
    $this->userW->field_edad->set($age);
  }

  public function setUserOpsex ($opsex) {
    $this->userW->field_genero->set($opsex);
  }

  public function delete () {
    $this->userW->delete();
  }

  /**
   * Saves an user.
   */
  public function saveUser () {
    $this->userW->save();
  }

  function __destruct() {
    unset($this->user);
    unset($this->userW);
  }

}


  