/**
 */
package org.example.witalia;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EObject;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Characteristic</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link org.example.witalia.Characteristic#getName <em>Name</em>}</li>
 *   <li>{@link org.example.witalia.Characteristic#getType <em>Type</em>}</li>
 *   <li>{@link org.example.witalia.Characteristic#getValues <em>Values</em>}</li>
 *   <li>{@link org.example.witalia.Characteristic#getMobilePhones <em>Mobile Phones</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.example.witalia.WitaliaPackage#getCharacteristic()
 * @model
 * @generated
 */
public interface Characteristic extends EObject {
    /**
     * Returns the value of the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Name</em>' attribute isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Name</em>' attribute.
     * @see #setName(String)
     * @see org.example.witalia.WitaliaPackage#getCharacteristic_Name()
     * @model unique="false"
     * @generated
     */
    String getName();

    /**
     * Sets the value of the '{@link org.example.witalia.Characteristic#getName <em>Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Name</em>' attribute.
     * @see #getName()
     * @generated
     */
    void setName(String value);

    /**
     * Returns the value of the '<em><b>Type</b></em>' attribute.
     * The literals are from the enumeration {@link org.example.witalia.CharacteristicType}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Type</em>' attribute isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Type</em>' attribute.
     * @see org.example.witalia.CharacteristicType
     * @see #setType(CharacteristicType)
     * @see org.example.witalia.WitaliaPackage#getCharacteristic_Type()
     * @model unique="false"
     * @generated
     */
    CharacteristicType getType();

    /**
     * Sets the value of the '{@link org.example.witalia.Characteristic#getType <em>Type</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Type</em>' attribute.
     * @see org.example.witalia.CharacteristicType
     * @see #getType()
     * @generated
     */
    void setType(CharacteristicType value);

    /**
     * Returns the value of the '<em><b>Values</b></em>' attribute list.
     * The list contents are of type {@link java.lang.String}.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Values</em>' attribute list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Values</em>' attribute list.
     * @see org.example.witalia.WitaliaPackage#getCharacteristic_Values()
     * @model unique="false"
     * @generated
     */
    EList<String> getValues();

    /**
     * Returns the value of the '<em><b>Mobile Phones</b></em>' reference list.
     * The list contents are of type {@link org.example.witalia.MobilePhone}.
     * It is bidirectional and its opposite is '{@link org.example.witalia.MobilePhone#getCharacteristics <em>Characteristics</em>}'.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Mobile Phones</em>' reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Mobile Phones</em>' reference list.
     * @see org.example.witalia.WitaliaPackage#getCharacteristic_MobilePhones()
     * @see org.example.witalia.MobilePhone#getCharacteristics
     * @model opposite="characteristics"
     * @generated
     */
    EList<MobilePhone> getMobilePhones();

} // Characteristic
