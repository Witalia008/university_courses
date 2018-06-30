/**
 */
package org.example.witalia;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EObject;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Manufacturer</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link org.example.witalia.Manufacturer#getName <em>Name</em>}</li>
 *   <li>{@link org.example.witalia.Manufacturer#getAddress <em>Address</em>}</li>
 *   <li>{@link org.example.witalia.Manufacturer#getPhone <em>Phone</em>}</li>
 *   <li>{@link org.example.witalia.Manufacturer#getRating <em>Rating</em>}</li>
 *   <li>{@link org.example.witalia.Manufacturer#getMobilePhones <em>Mobile Phones</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.example.witalia.WitaliaPackage#getManufacturer()
 * @model
 * @generated
 */
public interface Manufacturer extends EObject {
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
     * @see org.example.witalia.WitaliaPackage#getManufacturer_Name()
     * @model unique="false"
     * @generated
     */
    String getName();

    /**
     * Sets the value of the '{@link org.example.witalia.Manufacturer#getName <em>Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Name</em>' attribute.
     * @see #getName()
     * @generated
     */
    void setName(String value);

    /**
     * Returns the value of the '<em><b>Address</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Address</em>' attribute isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Address</em>' attribute.
     * @see #setAddress(String)
     * @see org.example.witalia.WitaliaPackage#getManufacturer_Address()
     * @model unique="false"
     * @generated
     */
    String getAddress();

    /**
     * Sets the value of the '{@link org.example.witalia.Manufacturer#getAddress <em>Address</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Address</em>' attribute.
     * @see #getAddress()
     * @generated
     */
    void setAddress(String value);

    /**
     * Returns the value of the '<em><b>Phone</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Phone</em>' attribute isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Phone</em>' attribute.
     * @see #setPhone(String)
     * @see org.example.witalia.WitaliaPackage#getManufacturer_Phone()
     * @model unique="false"
     * @generated
     */
    String getPhone();

    /**
     * Sets the value of the '{@link org.example.witalia.Manufacturer#getPhone <em>Phone</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Phone</em>' attribute.
     * @see #getPhone()
     * @generated
     */
    void setPhone(String value);

    /**
     * Returns the value of the '<em><b>Rating</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Rating</em>' attribute isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Rating</em>' attribute.
     * @see #setRating(int)
     * @see org.example.witalia.WitaliaPackage#getManufacturer_Rating()
     * @model unique="false"
     * @generated
     */
    int getRating();

    /**
     * Sets the value of the '{@link org.example.witalia.Manufacturer#getRating <em>Rating</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Rating</em>' attribute.
     * @see #getRating()
     * @generated
     */
    void setRating(int value);

    /**
     * Returns the value of the '<em><b>Mobile Phones</b></em>' containment reference list.
     * The list contents are of type {@link org.example.witalia.MobilePhone}.
     * It is bidirectional and its opposite is '{@link org.example.witalia.MobilePhone#getManufacturer <em>Manufacturer</em>}'.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Mobile Phones</em>' containment reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Mobile Phones</em>' containment reference list.
     * @see org.example.witalia.WitaliaPackage#getManufacturer_MobilePhones()
     * @see org.example.witalia.MobilePhone#getManufacturer
     * @model opposite="manufacturer" containment="true"
     * @generated
     */
    EList<MobilePhone> getMobilePhones();

} // Manufacturer
