/**
 */
package org.example.witalia.impl;

import java.util.Date;
import java.util.List;

import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EDataType;
import org.eclipse.emf.ecore.EEnum;
import org.eclipse.emf.ecore.EGenericType;
import org.eclipse.emf.ecore.EOperation;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.EReference;
import org.eclipse.emf.ecore.EcorePackage;

import org.eclipse.emf.ecore.impl.EPackageImpl;

import org.example.witalia.Characteristic;
import org.example.witalia.CharacteristicType;
import org.example.witalia.Manufacturer;
import org.example.witalia.MobilePhone;
import org.example.witalia.Store;
import org.example.witalia.WitaliaFactory;
import org.example.witalia.WitaliaPackage;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model <b>Package</b>.
 * <!-- end-user-doc -->
 * @generated
 */
public class WitaliaPackageImpl extends EPackageImpl implements WitaliaPackage {
    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass storeEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass mobilePhoneEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass manufacturerEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EClass characteristicEClass = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EEnum characteristicTypeEEnum = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EDataType dateEDataType = null;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private EDataType listEDataType = null;

    /**
     * Creates an instance of the model <b>Package</b>, registered with
     * {@link org.eclipse.emf.ecore.EPackage.Registry EPackage.Registry} by the package
     * package URI value.
     * <p>Note: the correct way to create the package is via the static
     * factory method {@link #init init()}, which also performs
     * initialization of the package, or returns the registered package,
     * if one already exists.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see org.eclipse.emf.ecore.EPackage.Registry
     * @see org.example.witalia.WitaliaPackage#eNS_URI
     * @see #init()
     * @generated
     */
    private WitaliaPackageImpl() {
        super(eNS_URI, WitaliaFactory.eINSTANCE);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private static boolean isInited = false;

    /**
     * Creates, registers, and initializes the <b>Package</b> for this model, and for any others upon which it depends.
     * 
     * <p>This method is used to initialize {@link WitaliaPackage#eINSTANCE} when that field is accessed.
     * Clients should not invoke it directly. Instead, they should simply access that field to obtain the package.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #eNS_URI
     * @see #createPackageContents()
     * @see #initializePackageContents()
     * @generated
     */
    public static WitaliaPackage init() {
        if (isInited) return (WitaliaPackage)EPackage.Registry.INSTANCE.getEPackage(WitaliaPackage.eNS_URI);

        // Obtain or create and register package
        WitaliaPackageImpl theWitaliaPackage = (WitaliaPackageImpl)(EPackage.Registry.INSTANCE.get(eNS_URI) instanceof WitaliaPackageImpl ? EPackage.Registry.INSTANCE.get(eNS_URI) : new WitaliaPackageImpl());

        isInited = true;

        // Initialize simple dependencies
        EcorePackage.eINSTANCE.eClass();

        // Create package meta-data objects
        theWitaliaPackage.createPackageContents();

        // Initialize created meta-data
        theWitaliaPackage.initializePackageContents();

        // Mark meta-data to indicate it can't be changed
        theWitaliaPackage.freeze();

  
        // Update the registry and return the package
        EPackage.Registry.INSTANCE.put(WitaliaPackage.eNS_URI, theWitaliaPackage);
        return theWitaliaPackage;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getStore() {
        return storeEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getStore_Phones() {
        return (EReference)storeEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EOperation getStore__GetByManufacturer__Manufacturer() {
        return storeEClass.getEOperations().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EOperation getStore__GetWithinPrice__double_double() {
        return storeEClass.getEOperations().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getMobilePhone() {
        return mobilePhoneEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getMobilePhone_Name() {
        return (EAttribute)mobilePhoneEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getMobilePhone_Model() {
        return (EAttribute)mobilePhoneEClass.getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getMobilePhone_Price() {
        return (EAttribute)mobilePhoneEClass.getEStructuralFeatures().get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getMobilePhone_Rating() {
        return (EAttribute)mobilePhoneEClass.getEStructuralFeatures().get(3);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getMobilePhone_ReleaseDate() {
        return (EAttribute)mobilePhoneEClass.getEStructuralFeatures().get(4);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getMobilePhone_Manufacturer() {
        return (EReference)mobilePhoneEClass.getEStructuralFeatures().get(5);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getMobilePhone_Characteristics() {
        return (EReference)mobilePhoneEClass.getEStructuralFeatures().get(6);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getMobilePhone_Stores() {
        return (EReference)mobilePhoneEClass.getEStructuralFeatures().get(7);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getManufacturer() {
        return manufacturerEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getManufacturer_Name() {
        return (EAttribute)manufacturerEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getManufacturer_Address() {
        return (EAttribute)manufacturerEClass.getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getManufacturer_Phone() {
        return (EAttribute)manufacturerEClass.getEStructuralFeatures().get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getManufacturer_Rating() {
        return (EAttribute)manufacturerEClass.getEStructuralFeatures().get(3);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getManufacturer_MobilePhones() {
        return (EReference)manufacturerEClass.getEStructuralFeatures().get(4);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EClass getCharacteristic() {
        return characteristicEClass;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getCharacteristic_Name() {
        return (EAttribute)characteristicEClass.getEStructuralFeatures().get(0);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getCharacteristic_Type() {
        return (EAttribute)characteristicEClass.getEStructuralFeatures().get(1);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EAttribute getCharacteristic_Values() {
        return (EAttribute)characteristicEClass.getEStructuralFeatures().get(2);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EReference getCharacteristic_MobilePhones() {
        return (EReference)characteristicEClass.getEStructuralFeatures().get(3);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EEnum getCharacteristicType() {
        return characteristicTypeEEnum;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EDataType getDate() {
        return dateEDataType;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EDataType getList() {
        return listEDataType;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public WitaliaFactory getWitaliaFactory() {
        return (WitaliaFactory)getEFactoryInstance();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private boolean isCreated = false;

    /**
     * Creates the meta-model objects for the package.  This method is
     * guarded to have no affect on any invocation but its first.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void createPackageContents() {
        if (isCreated) return;
        isCreated = true;

        // Create classes and their features
        storeEClass = createEClass(STORE);
        createEReference(storeEClass, STORE__PHONES);
        createEOperation(storeEClass, STORE___GET_BY_MANUFACTURER__MANUFACTURER);
        createEOperation(storeEClass, STORE___GET_WITHIN_PRICE__DOUBLE_DOUBLE);

        mobilePhoneEClass = createEClass(MOBILE_PHONE);
        createEAttribute(mobilePhoneEClass, MOBILE_PHONE__NAME);
        createEAttribute(mobilePhoneEClass, MOBILE_PHONE__MODEL);
        createEAttribute(mobilePhoneEClass, MOBILE_PHONE__PRICE);
        createEAttribute(mobilePhoneEClass, MOBILE_PHONE__RATING);
        createEAttribute(mobilePhoneEClass, MOBILE_PHONE__RELEASE_DATE);
        createEReference(mobilePhoneEClass, MOBILE_PHONE__MANUFACTURER);
        createEReference(mobilePhoneEClass, MOBILE_PHONE__CHARACTERISTICS);
        createEReference(mobilePhoneEClass, MOBILE_PHONE__STORES);

        manufacturerEClass = createEClass(MANUFACTURER);
        createEAttribute(manufacturerEClass, MANUFACTURER__NAME);
        createEAttribute(manufacturerEClass, MANUFACTURER__ADDRESS);
        createEAttribute(manufacturerEClass, MANUFACTURER__PHONE);
        createEAttribute(manufacturerEClass, MANUFACTURER__RATING);
        createEReference(manufacturerEClass, MANUFACTURER__MOBILE_PHONES);

        characteristicEClass = createEClass(CHARACTERISTIC);
        createEAttribute(characteristicEClass, CHARACTERISTIC__NAME);
        createEAttribute(characteristicEClass, CHARACTERISTIC__TYPE);
        createEAttribute(characteristicEClass, CHARACTERISTIC__VALUES);
        createEReference(characteristicEClass, CHARACTERISTIC__MOBILE_PHONES);

        // Create enums
        characteristicTypeEEnum = createEEnum(CHARACTERISTIC_TYPE);

        // Create data types
        dateEDataType = createEDataType(DATE);
        listEDataType = createEDataType(LIST);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private boolean isInitialized = false;

    /**
     * Complete the initialization of the package and its meta-model.  This
     * method is guarded to have no affect on any invocation but its first.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void initializePackageContents() {
        if (isInitialized) return;
        isInitialized = true;

        // Initialize package
        setName(eNAME);
        setNsPrefix(eNS_PREFIX);
        setNsURI(eNS_URI);

        // Obtain other dependent packages
        EcorePackage theEcorePackage = (EcorePackage)EPackage.Registry.INSTANCE.getEPackage(EcorePackage.eNS_URI);

        // Create type parameters
        addETypeParameter(listEDataType, "T");

        // Set bounds for type parameters

        // Add supertypes to classes

        // Initialize classes, features, and operations; add parameters
        initEClass(storeEClass, Store.class, "Store", !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEReference(getStore_Phones(), this.getMobilePhone(), this.getMobilePhone_Stores(), "phones", null, 0, -1, Store.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        EOperation op = initEOperation(getStore__GetByManufacturer__Manufacturer(), this.getMobilePhone(), "getByManufacturer", 0, 1, !IS_UNIQUE, IS_ORDERED);
        addEParameter(op, this.getManufacturer(), "man", 0, 1, !IS_UNIQUE, IS_ORDERED);

        op = initEOperation(getStore__GetWithinPrice__double_double(), null, "getWithinPrice", 0, 1, !IS_UNIQUE, IS_ORDERED);
        addEParameter(op, theEcorePackage.getEDouble(), "minPrice", 0, 1, !IS_UNIQUE, IS_ORDERED);
        addEParameter(op, theEcorePackage.getEDouble(), "maxPrice", 0, 1, !IS_UNIQUE, IS_ORDERED);
        EGenericType g1 = createEGenericType(this.getList());
        EGenericType g2 = createEGenericType(this.getMobilePhone());
        g1.getETypeArguments().add(g2);
        initEOperation(op, g1);

        initEClass(mobilePhoneEClass, MobilePhone.class, "MobilePhone", !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getMobilePhone_Name(), theEcorePackage.getEString(), "name", null, 0, 1, MobilePhone.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, !IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEAttribute(getMobilePhone_Model(), theEcorePackage.getEString(), "model", null, 0, 1, MobilePhone.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, !IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEAttribute(getMobilePhone_Price(), theEcorePackage.getEDouble(), "price", null, 0, 1, MobilePhone.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, !IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEAttribute(getMobilePhone_Rating(), theEcorePackage.getEInt(), "rating", null, 0, 1, MobilePhone.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, !IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEAttribute(getMobilePhone_ReleaseDate(), this.getDate(), "releaseDate", null, 0, 1, MobilePhone.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, !IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getMobilePhone_Manufacturer(), this.getManufacturer(), this.getManufacturer_MobilePhones(), "manufacturer", null, 0, 1, MobilePhone.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getMobilePhone_Characteristics(), this.getCharacteristic(), this.getCharacteristic_MobilePhones(), "characteristics", null, 0, -1, MobilePhone.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getMobilePhone_Stores(), this.getStore(), this.getStore_Phones(), "stores", null, 0, -1, MobilePhone.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(manufacturerEClass, Manufacturer.class, "Manufacturer", !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getManufacturer_Name(), theEcorePackage.getEString(), "name", null, 0, 1, Manufacturer.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, !IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEAttribute(getManufacturer_Address(), theEcorePackage.getEString(), "address", null, 0, 1, Manufacturer.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, !IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEAttribute(getManufacturer_Phone(), theEcorePackage.getEString(), "phone", null, 0, 1, Manufacturer.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, !IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEAttribute(getManufacturer_Rating(), theEcorePackage.getEInt(), "rating", null, 0, 1, Manufacturer.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, !IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getManufacturer_MobilePhones(), this.getMobilePhone(), this.getMobilePhone_Manufacturer(), "mobilePhones", null, 0, -1, Manufacturer.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, IS_COMPOSITE, !IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        initEClass(characteristicEClass, Characteristic.class, "Characteristic", !IS_ABSTRACT, !IS_INTERFACE, IS_GENERATED_INSTANCE_CLASS);
        initEAttribute(getCharacteristic_Name(), theEcorePackage.getEString(), "name", null, 0, 1, Characteristic.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, !IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEAttribute(getCharacteristic_Type(), this.getCharacteristicType(), "type", null, 0, 1, Characteristic.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, !IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEAttribute(getCharacteristic_Values(), theEcorePackage.getEString(), "values", null, 0, -1, Characteristic.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_UNSETTABLE, !IS_ID, !IS_UNIQUE, !IS_DERIVED, IS_ORDERED);
        initEReference(getCharacteristic_MobilePhones(), this.getMobilePhone(), this.getMobilePhone_Characteristics(), "mobilePhones", null, 0, -1, Characteristic.class, !IS_TRANSIENT, !IS_VOLATILE, IS_CHANGEABLE, !IS_COMPOSITE, IS_RESOLVE_PROXIES, !IS_UNSETTABLE, IS_UNIQUE, !IS_DERIVED, IS_ORDERED);

        // Initialize enums and add enum literals
        initEEnum(characteristicTypeEEnum, CharacteristicType.class, "CharacteristicType");
        addEEnumLiteral(characteristicTypeEEnum, CharacteristicType.HARDWARE);
        addEEnumLiteral(characteristicTypeEEnum, CharacteristicType.SOFTWARE);
        addEEnumLiteral(characteristicTypeEEnum, CharacteristicType.SUPPORT);

        // Initialize data types
        initEDataType(dateEDataType, Date.class, "Date", IS_SERIALIZABLE, !IS_GENERATED_INSTANCE_CLASS);
        initEDataType(listEDataType, List.class, "List", IS_SERIALIZABLE, !IS_GENERATED_INSTANCE_CLASS);

        // Create resource
        createResource(eNS_URI);
    }

} //WitaliaPackageImpl
