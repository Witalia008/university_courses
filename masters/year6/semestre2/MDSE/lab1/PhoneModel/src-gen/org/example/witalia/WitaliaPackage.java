/**
 */
package org.example.witalia;

import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EDataType;
import org.eclipse.emf.ecore.EEnum;
import org.eclipse.emf.ecore.EOperation;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.EReference;

/**
 * <!-- begin-user-doc -->
 * The <b>Package</b> for the model.
 * It contains accessors for the meta objects to represent
 * <ul>
 *   <li>each class,</li>
 *   <li>each feature of each class,</li>
 *   <li>each operation of each class,</li>
 *   <li>each enum,</li>
 *   <li>and each data type</li>
 * </ul>
 * <!-- end-user-doc -->
 * @see org.example.witalia.WitaliaFactory
 * @model kind="package"
 *        annotation="http://www.eclipse.org/emf/2002/GenModel basePackage='org.example'"
 * @generated
 */
public interface WitaliaPackage extends EPackage {
    /**
     * The package name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNAME = "witalia";

    /**
     * The package namespace URI.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_URI = "org.example.witalia";

    /**
     * The package namespace name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    String eNS_PREFIX = "witalia";

    /**
     * The singleton instance of the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    WitaliaPackage eINSTANCE = org.example.witalia.impl.WitaliaPackageImpl.init();

    /**
     * The meta object id for the '{@link org.example.witalia.impl.StoreImpl <em>Store</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.example.witalia.impl.StoreImpl
     * @see org.example.witalia.impl.WitaliaPackageImpl#getStore()
     * @generated
     */
    int STORE = 0;

    /**
     * The feature id for the '<em><b>Phones</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int STORE__PHONES = 0;

    /**
     * The number of structural features of the '<em>Store</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int STORE_FEATURE_COUNT = 1;

    /**
     * The operation id for the '<em>Get By Manufacturer</em>' operation.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int STORE___GET_BY_MANUFACTURER__MANUFACTURER = 0;

    /**
     * The operation id for the '<em>Get Within Price</em>' operation.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int STORE___GET_WITHIN_PRICE__DOUBLE_DOUBLE = 1;

    /**
     * The number of operations of the '<em>Store</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int STORE_OPERATION_COUNT = 2;

    /**
     * The meta object id for the '{@link org.example.witalia.impl.MobilePhoneImpl <em>Mobile Phone</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.example.witalia.impl.MobilePhoneImpl
     * @see org.example.witalia.impl.WitaliaPackageImpl#getMobilePhone()
     * @generated
     */
    int MOBILE_PHONE = 1;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int MOBILE_PHONE__NAME = 0;

    /**
     * The feature id for the '<em><b>Model</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int MOBILE_PHONE__MODEL = 1;

    /**
     * The feature id for the '<em><b>Price</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int MOBILE_PHONE__PRICE = 2;

    /**
     * The feature id for the '<em><b>Rating</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int MOBILE_PHONE__RATING = 3;

    /**
     * The feature id for the '<em><b>Release Date</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int MOBILE_PHONE__RELEASE_DATE = 4;

    /**
     * The feature id for the '<em><b>Manufacturer</b></em>' container reference.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int MOBILE_PHONE__MANUFACTURER = 5;

    /**
     * The feature id for the '<em><b>Characteristics</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int MOBILE_PHONE__CHARACTERISTICS = 6;

    /**
     * The feature id for the '<em><b>Stores</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int MOBILE_PHONE__STORES = 7;

    /**
     * The number of structural features of the '<em>Mobile Phone</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int MOBILE_PHONE_FEATURE_COUNT = 8;

    /**
     * The number of operations of the '<em>Mobile Phone</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int MOBILE_PHONE_OPERATION_COUNT = 0;

    /**
     * The meta object id for the '{@link org.example.witalia.impl.ManufacturerImpl <em>Manufacturer</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.example.witalia.impl.ManufacturerImpl
     * @see org.example.witalia.impl.WitaliaPackageImpl#getManufacturer()
     * @generated
     */
    int MANUFACTURER = 2;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int MANUFACTURER__NAME = 0;

    /**
     * The feature id for the '<em><b>Address</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int MANUFACTURER__ADDRESS = 1;

    /**
     * The feature id for the '<em><b>Phone</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int MANUFACTURER__PHONE = 2;

    /**
     * The feature id for the '<em><b>Rating</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int MANUFACTURER__RATING = 3;

    /**
     * The feature id for the '<em><b>Mobile Phones</b></em>' containment reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int MANUFACTURER__MOBILE_PHONES = 4;

    /**
     * The number of structural features of the '<em>Manufacturer</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int MANUFACTURER_FEATURE_COUNT = 5;

    /**
     * The number of operations of the '<em>Manufacturer</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int MANUFACTURER_OPERATION_COUNT = 0;

    /**
     * The meta object id for the '{@link org.example.witalia.impl.CharacteristicImpl <em>Characteristic</em>}' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.example.witalia.impl.CharacteristicImpl
     * @see org.example.witalia.impl.WitaliaPackageImpl#getCharacteristic()
     * @generated
     */
    int CHARACTERISTIC = 3;

    /**
     * The feature id for the '<em><b>Name</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CHARACTERISTIC__NAME = 0;

    /**
     * The feature id for the '<em><b>Type</b></em>' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CHARACTERISTIC__TYPE = 1;

    /**
     * The feature id for the '<em><b>Values</b></em>' attribute list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CHARACTERISTIC__VALUES = 2;

    /**
     * The feature id for the '<em><b>Mobile Phones</b></em>' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CHARACTERISTIC__MOBILE_PHONES = 3;

    /**
     * The number of structural features of the '<em>Characteristic</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CHARACTERISTIC_FEATURE_COUNT = 4;

    /**
     * The number of operations of the '<em>Characteristic</em>' class.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     * @ordered
     */
    int CHARACTERISTIC_OPERATION_COUNT = 0;

    /**
     * The meta object id for the '{@link org.example.witalia.CharacteristicType <em>Characteristic Type</em>}' enum.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.example.witalia.CharacteristicType
     * @see org.example.witalia.impl.WitaliaPackageImpl#getCharacteristicType()
     * @generated
     */
    int CHARACTERISTIC_TYPE = 4;

    /**
     * The meta object id for the '<em>Date</em>' data type.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see java.util.Date
     * @see org.example.witalia.impl.WitaliaPackageImpl#getDate()
     * @generated
     */
    int DATE = 5;

    /**
     * The meta object id for the '<em>List</em>' data type.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see java.util.List
     * @see org.example.witalia.impl.WitaliaPackageImpl#getList()
     * @generated
     */
    int LIST = 6;


    /**
     * Returns the meta object for class '{@link org.example.witalia.Store <em>Store</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Store</em>'.
     * @see org.example.witalia.Store
     * @generated
     */
    EClass getStore();

    /**
     * Returns the meta object for the reference list '{@link org.example.witalia.Store#getPhones <em>Phones</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Phones</em>'.
     * @see org.example.witalia.Store#getPhones()
     * @see #getStore()
     * @generated
     */
    EReference getStore_Phones();

    /**
     * Returns the meta object for the '{@link org.example.witalia.Store#getByManufacturer(org.example.witalia.Manufacturer) <em>Get By Manufacturer</em>}' operation.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the '<em>Get By Manufacturer</em>' operation.
     * @see org.example.witalia.Store#getByManufacturer(org.example.witalia.Manufacturer)
     * @generated
     */
    EOperation getStore__GetByManufacturer__Manufacturer();

    /**
     * Returns the meta object for the '{@link org.example.witalia.Store#getWithinPrice(double, double) <em>Get Within Price</em>}' operation.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the '<em>Get Within Price</em>' operation.
     * @see org.example.witalia.Store#getWithinPrice(double, double)
     * @generated
     */
    EOperation getStore__GetWithinPrice__double_double();

    /**
     * Returns the meta object for class '{@link org.example.witalia.MobilePhone <em>Mobile Phone</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Mobile Phone</em>'.
     * @see org.example.witalia.MobilePhone
     * @generated
     */
    EClass getMobilePhone();

    /**
     * Returns the meta object for the attribute '{@link org.example.witalia.MobilePhone#getName <em>Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Name</em>'.
     * @see org.example.witalia.MobilePhone#getName()
     * @see #getMobilePhone()
     * @generated
     */
    EAttribute getMobilePhone_Name();

    /**
     * Returns the meta object for the attribute '{@link org.example.witalia.MobilePhone#getModel <em>Model</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Model</em>'.
     * @see org.example.witalia.MobilePhone#getModel()
     * @see #getMobilePhone()
     * @generated
     */
    EAttribute getMobilePhone_Model();

    /**
     * Returns the meta object for the attribute '{@link org.example.witalia.MobilePhone#getPrice <em>Price</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Price</em>'.
     * @see org.example.witalia.MobilePhone#getPrice()
     * @see #getMobilePhone()
     * @generated
     */
    EAttribute getMobilePhone_Price();

    /**
     * Returns the meta object for the attribute '{@link org.example.witalia.MobilePhone#getRating <em>Rating</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Rating</em>'.
     * @see org.example.witalia.MobilePhone#getRating()
     * @see #getMobilePhone()
     * @generated
     */
    EAttribute getMobilePhone_Rating();

    /**
     * Returns the meta object for the attribute '{@link org.example.witalia.MobilePhone#getReleaseDate <em>Release Date</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Release Date</em>'.
     * @see org.example.witalia.MobilePhone#getReleaseDate()
     * @see #getMobilePhone()
     * @generated
     */
    EAttribute getMobilePhone_ReleaseDate();

    /**
     * Returns the meta object for the container reference '{@link org.example.witalia.MobilePhone#getManufacturer <em>Manufacturer</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the container reference '<em>Manufacturer</em>'.
     * @see org.example.witalia.MobilePhone#getManufacturer()
     * @see #getMobilePhone()
     * @generated
     */
    EReference getMobilePhone_Manufacturer();

    /**
     * Returns the meta object for the reference list '{@link org.example.witalia.MobilePhone#getCharacteristics <em>Characteristics</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Characteristics</em>'.
     * @see org.example.witalia.MobilePhone#getCharacteristics()
     * @see #getMobilePhone()
     * @generated
     */
    EReference getMobilePhone_Characteristics();

    /**
     * Returns the meta object for the reference list '{@link org.example.witalia.MobilePhone#getStores <em>Stores</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Stores</em>'.
     * @see org.example.witalia.MobilePhone#getStores()
     * @see #getMobilePhone()
     * @generated
     */
    EReference getMobilePhone_Stores();

    /**
     * Returns the meta object for class '{@link org.example.witalia.Manufacturer <em>Manufacturer</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Manufacturer</em>'.
     * @see org.example.witalia.Manufacturer
     * @generated
     */
    EClass getManufacturer();

    /**
     * Returns the meta object for the attribute '{@link org.example.witalia.Manufacturer#getName <em>Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Name</em>'.
     * @see org.example.witalia.Manufacturer#getName()
     * @see #getManufacturer()
     * @generated
     */
    EAttribute getManufacturer_Name();

    /**
     * Returns the meta object for the attribute '{@link org.example.witalia.Manufacturer#getAddress <em>Address</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Address</em>'.
     * @see org.example.witalia.Manufacturer#getAddress()
     * @see #getManufacturer()
     * @generated
     */
    EAttribute getManufacturer_Address();

    /**
     * Returns the meta object for the attribute '{@link org.example.witalia.Manufacturer#getPhone <em>Phone</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Phone</em>'.
     * @see org.example.witalia.Manufacturer#getPhone()
     * @see #getManufacturer()
     * @generated
     */
    EAttribute getManufacturer_Phone();

    /**
     * Returns the meta object for the attribute '{@link org.example.witalia.Manufacturer#getRating <em>Rating</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Rating</em>'.
     * @see org.example.witalia.Manufacturer#getRating()
     * @see #getManufacturer()
     * @generated
     */
    EAttribute getManufacturer_Rating();

    /**
     * Returns the meta object for the containment reference list '{@link org.example.witalia.Manufacturer#getMobilePhones <em>Mobile Phones</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the containment reference list '<em>Mobile Phones</em>'.
     * @see org.example.witalia.Manufacturer#getMobilePhones()
     * @see #getManufacturer()
     * @generated
     */
    EReference getManufacturer_MobilePhones();

    /**
     * Returns the meta object for class '{@link org.example.witalia.Characteristic <em>Characteristic</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for class '<em>Characteristic</em>'.
     * @see org.example.witalia.Characteristic
     * @generated
     */
    EClass getCharacteristic();

    /**
     * Returns the meta object for the attribute '{@link org.example.witalia.Characteristic#getName <em>Name</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Name</em>'.
     * @see org.example.witalia.Characteristic#getName()
     * @see #getCharacteristic()
     * @generated
     */
    EAttribute getCharacteristic_Name();

    /**
     * Returns the meta object for the attribute '{@link org.example.witalia.Characteristic#getType <em>Type</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute '<em>Type</em>'.
     * @see org.example.witalia.Characteristic#getType()
     * @see #getCharacteristic()
     * @generated
     */
    EAttribute getCharacteristic_Type();

    /**
     * Returns the meta object for the attribute list '{@link org.example.witalia.Characteristic#getValues <em>Values</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the attribute list '<em>Values</em>'.
     * @see org.example.witalia.Characteristic#getValues()
     * @see #getCharacteristic()
     * @generated
     */
    EAttribute getCharacteristic_Values();

    /**
     * Returns the meta object for the reference list '{@link org.example.witalia.Characteristic#getMobilePhones <em>Mobile Phones</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for the reference list '<em>Mobile Phones</em>'.
     * @see org.example.witalia.Characteristic#getMobilePhones()
     * @see #getCharacteristic()
     * @generated
     */
    EReference getCharacteristic_MobilePhones();

    /**
     * Returns the meta object for enum '{@link org.example.witalia.CharacteristicType <em>Characteristic Type</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for enum '<em>Characteristic Type</em>'.
     * @see org.example.witalia.CharacteristicType
     * @generated
     */
    EEnum getCharacteristicType();

    /**
     * Returns the meta object for data type '{@link java.util.Date <em>Date</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for data type '<em>Date</em>'.
     * @see java.util.Date
     * @model instanceClass="java.util.Date"
     *        annotation="http://www.eclipse.org/emf/2002/GenModel create='<%java.util.Date%> _xtrycatchfinallyexpression = null;\ntry\n{\n\t<%java.util.Date%> _xifexpression = null;\n\tboolean _notEquals = (!<%com.google.common.base.Objects%>.equal(it, null));\n\tif (_notEquals)\n\t{\n\t\t<%java.text.SimpleDateFormat%> _simpleDateFormat = new <%java.text.SimpleDateFormat%>(\"yyyy-MM-dd\");\n\t\t<%java.util.Date%> _parse = _simpleDateFormat.parse(it);\n\t\t_xifexpression = _parse;\n\t}\n\t_xtrycatchfinallyexpression = _xifexpression;\n}\ncatch (final Throwable _t) {\n\tif (_t instanceof <%java.text.ParseException%>) {\n\t\tfinal <%java.text.ParseException%> ex = (<%java.text.ParseException%>)_t;\n\t\t<%java.lang.RuntimeException%> _runtimeException = new <%java.lang.RuntimeException%>(ex);\n\t\tthrow _runtimeException;\n\t}\n\telse\n\t{\n\t\tthrow <%org.eclipse.xtext.xbase.lib.Exceptions%>.sneakyThrow(_t);\n\t}\n}\nreturn _xtrycatchfinallyexpression;' convert='<%java.lang.String%> _xifexpression = null;\nboolean _notEquals = (!<%com.google.common.base.Objects%>.equal(it, null));\nif (_notEquals)\n{\n\t<%java.text.SimpleDateFormat%> _simpleDateFormat = new <%java.text.SimpleDateFormat%>(\"yyyy-MM-dd\");\n\t<%java.lang.String%> _format = _simpleDateFormat.format(it);\n\t_xifexpression = _format;\n}\nreturn _xifexpression;'"
     * @generated
     */
    EDataType getDate();

    /**
     * Returns the meta object for data type '{@link java.util.List <em>List</em>}'.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the meta object for data type '<em>List</em>'.
     * @see java.util.List
     * @model instanceClass="java.util.List" typeParameters="T"
     * @generated
     */
    EDataType getList();

    /**
     * Returns the factory that creates the instances of the model.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @return the factory that creates the instances of the model.
     * @generated
     */
    WitaliaFactory getWitaliaFactory();

    /**
     * <!-- begin-user-doc -->
     * Defines literals for the meta objects that represent
     * <ul>
     *   <li>each class,</li>
     *   <li>each feature of each class,</li>
     *   <li>each operation of each class,</li>
     *   <li>each enum,</li>
     *   <li>and each data type</li>
     * </ul>
     * <!-- end-user-doc -->
     * @generated
     */
    interface Literals {
        /**
         * The meta object literal for the '{@link org.example.witalia.impl.StoreImpl <em>Store</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see org.example.witalia.impl.StoreImpl
         * @see org.example.witalia.impl.WitaliaPackageImpl#getStore()
         * @generated
         */
        EClass STORE = eINSTANCE.getStore();

        /**
         * The meta object literal for the '<em><b>Phones</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference STORE__PHONES = eINSTANCE.getStore_Phones();

        /**
         * The meta object literal for the '<em><b>Get By Manufacturer</b></em>' operation.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EOperation STORE___GET_BY_MANUFACTURER__MANUFACTURER = eINSTANCE.getStore__GetByManufacturer__Manufacturer();

        /**
         * The meta object literal for the '<em><b>Get Within Price</b></em>' operation.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EOperation STORE___GET_WITHIN_PRICE__DOUBLE_DOUBLE = eINSTANCE.getStore__GetWithinPrice__double_double();

        /**
         * The meta object literal for the '{@link org.example.witalia.impl.MobilePhoneImpl <em>Mobile Phone</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see org.example.witalia.impl.MobilePhoneImpl
         * @see org.example.witalia.impl.WitaliaPackageImpl#getMobilePhone()
         * @generated
         */
        EClass MOBILE_PHONE = eINSTANCE.getMobilePhone();

        /**
         * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute MOBILE_PHONE__NAME = eINSTANCE.getMobilePhone_Name();

        /**
         * The meta object literal for the '<em><b>Model</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute MOBILE_PHONE__MODEL = eINSTANCE.getMobilePhone_Model();

        /**
         * The meta object literal for the '<em><b>Price</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute MOBILE_PHONE__PRICE = eINSTANCE.getMobilePhone_Price();

        /**
         * The meta object literal for the '<em><b>Rating</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute MOBILE_PHONE__RATING = eINSTANCE.getMobilePhone_Rating();

        /**
         * The meta object literal for the '<em><b>Release Date</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute MOBILE_PHONE__RELEASE_DATE = eINSTANCE.getMobilePhone_ReleaseDate();

        /**
         * The meta object literal for the '<em><b>Manufacturer</b></em>' container reference feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference MOBILE_PHONE__MANUFACTURER = eINSTANCE.getMobilePhone_Manufacturer();

        /**
         * The meta object literal for the '<em><b>Characteristics</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference MOBILE_PHONE__CHARACTERISTICS = eINSTANCE.getMobilePhone_Characteristics();

        /**
         * The meta object literal for the '<em><b>Stores</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference MOBILE_PHONE__STORES = eINSTANCE.getMobilePhone_Stores();

        /**
         * The meta object literal for the '{@link org.example.witalia.impl.ManufacturerImpl <em>Manufacturer</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see org.example.witalia.impl.ManufacturerImpl
         * @see org.example.witalia.impl.WitaliaPackageImpl#getManufacturer()
         * @generated
         */
        EClass MANUFACTURER = eINSTANCE.getManufacturer();

        /**
         * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute MANUFACTURER__NAME = eINSTANCE.getManufacturer_Name();

        /**
         * The meta object literal for the '<em><b>Address</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute MANUFACTURER__ADDRESS = eINSTANCE.getManufacturer_Address();

        /**
         * The meta object literal for the '<em><b>Phone</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute MANUFACTURER__PHONE = eINSTANCE.getManufacturer_Phone();

        /**
         * The meta object literal for the '<em><b>Rating</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute MANUFACTURER__RATING = eINSTANCE.getManufacturer_Rating();

        /**
         * The meta object literal for the '<em><b>Mobile Phones</b></em>' containment reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference MANUFACTURER__MOBILE_PHONES = eINSTANCE.getManufacturer_MobilePhones();

        /**
         * The meta object literal for the '{@link org.example.witalia.impl.CharacteristicImpl <em>Characteristic</em>}' class.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see org.example.witalia.impl.CharacteristicImpl
         * @see org.example.witalia.impl.WitaliaPackageImpl#getCharacteristic()
         * @generated
         */
        EClass CHARACTERISTIC = eINSTANCE.getCharacteristic();

        /**
         * The meta object literal for the '<em><b>Name</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute CHARACTERISTIC__NAME = eINSTANCE.getCharacteristic_Name();

        /**
         * The meta object literal for the '<em><b>Type</b></em>' attribute feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute CHARACTERISTIC__TYPE = eINSTANCE.getCharacteristic_Type();

        /**
         * The meta object literal for the '<em><b>Values</b></em>' attribute list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EAttribute CHARACTERISTIC__VALUES = eINSTANCE.getCharacteristic_Values();

        /**
         * The meta object literal for the '<em><b>Mobile Phones</b></em>' reference list feature.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @generated
         */
        EReference CHARACTERISTIC__MOBILE_PHONES = eINSTANCE.getCharacteristic_MobilePhones();

        /**
         * The meta object literal for the '{@link org.example.witalia.CharacteristicType <em>Characteristic Type</em>}' enum.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see org.example.witalia.CharacteristicType
         * @see org.example.witalia.impl.WitaliaPackageImpl#getCharacteristicType()
         * @generated
         */
        EEnum CHARACTERISTIC_TYPE = eINSTANCE.getCharacteristicType();

        /**
         * The meta object literal for the '<em>Date</em>' data type.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see java.util.Date
         * @see org.example.witalia.impl.WitaliaPackageImpl#getDate()
         * @generated
         */
        EDataType DATE = eINSTANCE.getDate();

        /**
         * The meta object literal for the '<em>List</em>' data type.
         * <!-- begin-user-doc -->
         * <!-- end-user-doc -->
         * @see java.util.List
         * @see org.example.witalia.impl.WitaliaPackageImpl#getList()
         * @generated
         */
        EDataType LIST = eINSTANCE.getList();

    }

} //WitaliaPackage
