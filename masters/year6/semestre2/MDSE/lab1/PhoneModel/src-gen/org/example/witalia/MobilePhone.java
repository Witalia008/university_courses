/**
 */
package org.example.witalia;

import java.util.Date;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EObject;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Mobile Phone</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link org.example.witalia.MobilePhone#getName <em>Name</em>}</li>
 *   <li>{@link org.example.witalia.MobilePhone#getModel <em>Model</em>}</li>
 *   <li>{@link org.example.witalia.MobilePhone#getPrice <em>Price</em>}</li>
 *   <li>{@link org.example.witalia.MobilePhone#getRating <em>Rating</em>}</li>
 *   <li>{@link org.example.witalia.MobilePhone#getReleaseDate <em>Release Date</em>}</li>
 *   <li>{@link org.example.witalia.MobilePhone#getManufacturer <em>Manufacturer</em>}</li>
 *   <li>{@link org.example.witalia.MobilePhone#getCharacteristics <em>Characteristics</em>}</li>
 *   <li>{@link org.example.witalia.MobilePhone#getStores <em>Stores</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.example.witalia.WitaliaPackage#getMobilePhone()
 * @model
 * @generated
 */
public interface MobilePhone extends EObject {
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
     * @see org.example.witalia.WitaliaPackage#getMobilePhone_Name()
     * @model unique="false"
     * @generated
     */
    String getName();

    /**
     * Sets the value of the '{@link org.example.witalia.MobilePhone#getName <em>Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Name</em>' attribute.
     * @see #getName()
     * @generated
     */
    void setName(String value);

    /**
     * Returns the value of the '<em><b>Model</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Model</em>' attribute isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Model</em>' attribute.
     * @see #setModel(String)
     * @see org.example.witalia.WitaliaPackage#getMobilePhone_Model()
     * @model unique="false"
     * @generated
     */
    String getModel();

    /**
     * Sets the value of the '{@link org.example.witalia.MobilePhone#getModel <em>Model</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Model</em>' attribute.
     * @see #getModel()
     * @generated
     */
    void setModel(String value);

    /**
     * Returns the value of the '<em><b>Price</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Price</em>' attribute isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Price</em>' attribute.
     * @see #setPrice(double)
     * @see org.example.witalia.WitaliaPackage#getMobilePhone_Price()
     * @model unique="false"
     * @generated
     */
    double getPrice();

    /**
     * Sets the value of the '{@link org.example.witalia.MobilePhone#getPrice <em>Price</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Price</em>' attribute.
     * @see #getPrice()
     * @generated
     */
    void setPrice(double value);

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
     * @see org.example.witalia.WitaliaPackage#getMobilePhone_Rating()
     * @model unique="false"
     * @generated
     */
    int getRating();

    /**
     * Sets the value of the '{@link org.example.witalia.MobilePhone#getRating <em>Rating</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Rating</em>' attribute.
     * @see #getRating()
     * @generated
     */
    void setRating(int value);

    /**
     * Returns the value of the '<em><b>Release Date</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Release Date</em>' attribute isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Release Date</em>' attribute.
     * @see #setReleaseDate(Date)
     * @see org.example.witalia.WitaliaPackage#getMobilePhone_ReleaseDate()
     * @model unique="false" dataType="org.example.witalia.Date"
     * @generated
     */
    Date getReleaseDate();

    /**
     * Sets the value of the '{@link org.example.witalia.MobilePhone#getReleaseDate <em>Release Date</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Release Date</em>' attribute.
     * @see #getReleaseDate()
     * @generated
     */
    void setReleaseDate(Date value);

    /**
     * Returns the value of the '<em><b>Manufacturer</b></em>' container reference.
     * It is bidirectional and its opposite is '{@link org.example.witalia.Manufacturer#getMobilePhones <em>Mobile Phones</em>}'.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Manufacturer</em>' container reference isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Manufacturer</em>' container reference.
     * @see #setManufacturer(Manufacturer)
     * @see org.example.witalia.WitaliaPackage#getMobilePhone_Manufacturer()
     * @see org.example.witalia.Manufacturer#getMobilePhones
     * @model opposite="mobilePhones" transient="false"
     * @generated
     */
    Manufacturer getManufacturer();

    /**
     * Sets the value of the '{@link org.example.witalia.MobilePhone#getManufacturer <em>Manufacturer</em>}' container reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @param value the new value of the '<em>Manufacturer</em>' container reference.
     * @see #getManufacturer()
     * @generated
     */
    void setManufacturer(Manufacturer value);

    /**
     * Returns the value of the '<em><b>Characteristics</b></em>' reference list.
     * The list contents are of type {@link org.example.witalia.Characteristic}.
     * It is bidirectional and its opposite is '{@link org.example.witalia.Characteristic#getMobilePhones <em>Mobile Phones</em>}'.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Characteristics</em>' reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Characteristics</em>' reference list.
     * @see org.example.witalia.WitaliaPackage#getMobilePhone_Characteristics()
     * @see org.example.witalia.Characteristic#getMobilePhones
     * @model opposite="mobilePhones"
     * @generated
     */
    EList<Characteristic> getCharacteristics();

    /**
     * Returns the value of the '<em><b>Stores</b></em>' reference list.
     * The list contents are of type {@link org.example.witalia.Store}.
     * It is bidirectional and its opposite is '{@link org.example.witalia.Store#getPhones <em>Phones</em>}'.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Stores</em>' reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Stores</em>' reference list.
     * @see org.example.witalia.WitaliaPackage#getMobilePhone_Stores()
     * @see org.example.witalia.Store#getPhones
     * @model opposite="phones"
     * @generated
     */
    EList<Store> getStores();

} // MobilePhone
