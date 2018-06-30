/**
 */
package org.example.witalia;

import org.eclipse.emf.ecore.EFactory;

/**
 * <!-- begin-user-doc -->
 * The <b>Factory</b> for the model.
 * It provides a create method for each non-abstract class of the model.
 * <!-- end-user-doc -->
 * @see org.example.witalia.WitaliaPackage
 * @generated
 */
public interface WitaliaFactory extends EFactory {
    /**
     * The singleton instance of the factory.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    WitaliaFactory eINSTANCE = org.example.witalia.impl.WitaliaFactoryImpl.init();

    /**
     * Returns a new object of class '<em>Store</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Store</em>'.
     * @generated
     */
    Store createStore();

    /**
     * Returns a new object of class '<em>Mobile Phone</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Mobile Phone</em>'.
     * @generated
     */
    MobilePhone createMobilePhone();

    /**
     * Returns a new object of class '<em>Manufacturer</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Manufacturer</em>'.
     * @generated
     */
    Manufacturer createManufacturer();

    /**
     * Returns a new object of class '<em>Characteristic</em>'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return a new object of class '<em>Characteristic</em>'.
     * @generated
     */
    Characteristic createCharacteristic();

    /**
     * Returns the package supported by this factory.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the package supported by this factory.
     * @generated
     */
    WitaliaPackage getWitaliaPackage();

} //WitaliaFactory
