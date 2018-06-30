/**
 */
package org.example.witalia.impl;

import com.google.common.base.Objects;

import java.text.ParseException;
import java.text.SimpleDateFormat;

import java.util.Date;
import java.util.List;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EDataType;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;

import org.eclipse.emf.ecore.impl.EFactoryImpl;

import org.eclipse.emf.ecore.plugin.EcorePlugin;

import org.eclipse.xtext.xbase.lib.Exceptions;

import org.example.witalia.*;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model <b>Factory</b>.
 * <!-- end-user-doc -->
 * @generated
 */
public class WitaliaFactoryImpl extends EFactoryImpl implements WitaliaFactory {
    /**
     * Creates the default factory implementation.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static WitaliaFactory init() {
        try {
            WitaliaFactory theWitaliaFactory = (WitaliaFactory)EPackage.Registry.INSTANCE.getEFactory(WitaliaPackage.eNS_URI);
            if (theWitaliaFactory != null) {
                return theWitaliaFactory;
            }
        }
        catch (Exception exception) {
            EcorePlugin.INSTANCE.log(exception);
        }
        return new WitaliaFactoryImpl();
    }

    /**
     * Creates an instance of the factory.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public WitaliaFactoryImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public EObject create(EClass eClass) {
        switch (eClass.getClassifierID()) {
            case WitaliaPackage.STORE: return createStore();
            case WitaliaPackage.MOBILE_PHONE: return createMobilePhone();
            case WitaliaPackage.MANUFACTURER: return createManufacturer();
            case WitaliaPackage.CHARACTERISTIC: return createCharacteristic();
            default:
                throw new IllegalArgumentException("The class '" + eClass.getName() + "' is not a valid classifier");
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object createFromString(EDataType eDataType, String initialValue) {
        switch (eDataType.getClassifierID()) {
            case WitaliaPackage.CHARACTERISTIC_TYPE:
                return createCharacteristicTypeFromString(eDataType, initialValue);
            case WitaliaPackage.DATE:
                return createDateFromString(eDataType, initialValue);
            case WitaliaPackage.LIST:
                return createListFromString(eDataType, initialValue);
            default:
                throw new IllegalArgumentException("The datatype '" + eDataType.getName() + "' is not a valid classifier");
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public String convertToString(EDataType eDataType, Object instanceValue) {
        switch (eDataType.getClassifierID()) {
            case WitaliaPackage.CHARACTERISTIC_TYPE:
                return convertCharacteristicTypeToString(eDataType, instanceValue);
            case WitaliaPackage.DATE:
                return convertDateToString(eDataType, instanceValue);
            case WitaliaPackage.LIST:
                return convertListToString(eDataType, instanceValue);
            default:
                throw new IllegalArgumentException("The datatype '" + eDataType.getName() + "' is not a valid classifier");
        }
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public Store createStore() {
        StoreImpl store = new StoreImpl();
        return store;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public MobilePhone createMobilePhone() {
        MobilePhoneImpl mobilePhone = new MobilePhoneImpl();
        return mobilePhone;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public Manufacturer createManufacturer() {
        ManufacturerImpl manufacturer = new ManufacturerImpl();
        return manufacturer;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public Characteristic createCharacteristic() {
        CharacteristicImpl characteristic = new CharacteristicImpl();
        return characteristic;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public CharacteristicType createCharacteristicTypeFromString(EDataType eDataType, String initialValue) {
        CharacteristicType result = CharacteristicType.get(initialValue);
        if (result == null) throw new IllegalArgumentException("The value '" + initialValue + "' is not a valid enumerator of '" + eDataType.getName() + "'");
        return result;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public String convertCharacteristicTypeToString(EDataType eDataType, Object instanceValue) {
        return instanceValue == null ? null : instanceValue.toString();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public Date createDate(final String it) {
        Date _xtrycatchfinallyexpression = null;
        try {
            Date _xifexpression = null;
            boolean _notEquals = (!Objects.equal(it, null));
            if (_notEquals) {
                SimpleDateFormat _simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");
                Date _parse = _simpleDateFormat.parse(it);
                _xifexpression = _parse;
            }
            _xtrycatchfinallyexpression = _xifexpression;
        }
        catch (final Throwable _t) {
            if (_t instanceof ParseException) {
                final ParseException ex = (ParseException)_t;
                RuntimeException _runtimeException = new RuntimeException(ex);
                throw _runtimeException;
            }
            else {
                throw Exceptions.sneakyThrow(_t);
            }
        }
        return _xtrycatchfinallyexpression;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public Date createDateFromString(EDataType eDataType, String initialValue) {
        return createDate(initialValue);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public String convertDate(final Date it) {
        String _xifexpression = null;
        boolean _notEquals = (!Objects.equal(it, null));
        if (_notEquals) {
            SimpleDateFormat _simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");
            String _format = _simpleDateFormat.format(it);
            _xifexpression = _format;
        }
        return _xifexpression;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public String convertDateToString(EDataType eDataType, Object instanceValue) {
        return convertDate((Date)instanceValue);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public List<?> createListFromString(EDataType eDataType, String initialValue) {
        return (List<?>)super.createFromString(initialValue);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public String convertListToString(EDataType eDataType, Object instanceValue) {
        return super.convertToString(instanceValue);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public WitaliaPackage getWitaliaPackage() {
        return (WitaliaPackage)getEPackage();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @deprecated
     * @generated
     */
    @Deprecated
    public static WitaliaPackage getPackage() {
        return WitaliaPackage.eINSTANCE;
    }

} //WitaliaFactoryImpl
