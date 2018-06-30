/**
 */
package org.example.witalia.impl;

import java.util.Collection;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import org.eclipse.emf.ecore.impl.MinimalEObjectImpl;

import org.eclipse.emf.ecore.util.EDataTypeEList;
import org.eclipse.emf.ecore.util.EObjectWithInverseResolvingEList;
import org.eclipse.emf.ecore.util.InternalEList;

import org.example.witalia.Characteristic;
import org.example.witalia.CharacteristicType;
import org.example.witalia.MobilePhone;
import org.example.witalia.WitaliaPackage;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Characteristic</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * <ul>
 *   <li>{@link org.example.witalia.impl.CharacteristicImpl#getName <em>Name</em>}</li>
 *   <li>{@link org.example.witalia.impl.CharacteristicImpl#getType <em>Type</em>}</li>
 *   <li>{@link org.example.witalia.impl.CharacteristicImpl#getValues <em>Values</em>}</li>
 *   <li>{@link org.example.witalia.impl.CharacteristicImpl#getMobilePhones <em>Mobile Phones</em>}</li>
 * </ul>
 * </p>
 *
 * @generated
 */
public class CharacteristicImpl extends MinimalEObjectImpl.Container implements Characteristic {
    /**
     * The default value of the '{@link #getName() <em>Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getName()
     * @generated
     * @ordered
     */
    protected static final String NAME_EDEFAULT = null;

    /**
     * The cached value of the '{@link #getName() <em>Name</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getName()
     * @generated
     * @ordered
     */
    protected String name = NAME_EDEFAULT;

    /**
     * The default value of the '{@link #getType() <em>Type</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getType()
     * @generated
     * @ordered
     */
    protected static final CharacteristicType TYPE_EDEFAULT = CharacteristicType.HARDWARE;

    /**
     * The cached value of the '{@link #getType() <em>Type</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getType()
     * @generated
     * @ordered
     */
    protected CharacteristicType type = TYPE_EDEFAULT;

    /**
     * The cached value of the '{@link #getValues() <em>Values</em>}' attribute list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getValues()
     * @generated
     * @ordered
     */
    protected EList<String> values;

    /**
     * The cached value of the '{@link #getMobilePhones() <em>Mobile Phones</em>}' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getMobilePhones()
     * @generated
     * @ordered
     */
    protected EList<MobilePhone> mobilePhones;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected CharacteristicImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return WitaliaPackage.Literals.CHARACTERISTIC;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public String getName() {
        return name;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setName(String newName) {
        String oldName = name;
        name = newName;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET, WitaliaPackage.CHARACTERISTIC__NAME, oldName, name));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public CharacteristicType getType() {
        return type;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setType(CharacteristicType newType) {
        CharacteristicType oldType = type;
        type = newType == null ? TYPE_EDEFAULT : newType;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET, WitaliaPackage.CHARACTERISTIC__TYPE, oldType, type));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<String> getValues() {
        if (values == null) {
            values = new EDataTypeEList<String>(String.class, this, WitaliaPackage.CHARACTERISTIC__VALUES);
        }
        return values;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<MobilePhone> getMobilePhones() {
        if (mobilePhones == null) {
            mobilePhones = new EObjectWithInverseResolvingEList.ManyInverse<MobilePhone>(MobilePhone.class, this, WitaliaPackage.CHARACTERISTIC__MOBILE_PHONES, WitaliaPackage.MOBILE_PHONE__CHARACTERISTICS);
        }
        return mobilePhones;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @SuppressWarnings("unchecked")
    @Override
    public NotificationChain eInverseAdd(InternalEObject otherEnd, int featureID, NotificationChain msgs) {
        switch (featureID) {
            case WitaliaPackage.CHARACTERISTIC__MOBILE_PHONES:
                return ((InternalEList<InternalEObject>)(InternalEList<?>)getMobilePhones()).basicAdd(otherEnd, msgs);
        }
        return super.eInverseAdd(otherEnd, featureID, msgs);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public NotificationChain eInverseRemove(InternalEObject otherEnd, int featureID, NotificationChain msgs) {
        switch (featureID) {
            case WitaliaPackage.CHARACTERISTIC__MOBILE_PHONES:
                return ((InternalEList<?>)getMobilePhones()).basicRemove(otherEnd, msgs);
        }
        return super.eInverseRemove(otherEnd, featureID, msgs);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eGet(int featureID, boolean resolve, boolean coreType) {
        switch (featureID) {
            case WitaliaPackage.CHARACTERISTIC__NAME:
                return getName();
            case WitaliaPackage.CHARACTERISTIC__TYPE:
                return getType();
            case WitaliaPackage.CHARACTERISTIC__VALUES:
                return getValues();
            case WitaliaPackage.CHARACTERISTIC__MOBILE_PHONES:
                return getMobilePhones();
        }
        return super.eGet(featureID, resolve, coreType);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @SuppressWarnings("unchecked")
    @Override
    public void eSet(int featureID, Object newValue) {
        switch (featureID) {
            case WitaliaPackage.CHARACTERISTIC__NAME:
                setName((String)newValue);
                return;
            case WitaliaPackage.CHARACTERISTIC__TYPE:
                setType((CharacteristicType)newValue);
                return;
            case WitaliaPackage.CHARACTERISTIC__VALUES:
                getValues().clear();
                getValues().addAll((Collection<? extends String>)newValue);
                return;
            case WitaliaPackage.CHARACTERISTIC__MOBILE_PHONES:
                getMobilePhones().clear();
                getMobilePhones().addAll((Collection<? extends MobilePhone>)newValue);
                return;
        }
        super.eSet(featureID, newValue);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public void eUnset(int featureID) {
        switch (featureID) {
            case WitaliaPackage.CHARACTERISTIC__NAME:
                setName(NAME_EDEFAULT);
                return;
            case WitaliaPackage.CHARACTERISTIC__TYPE:
                setType(TYPE_EDEFAULT);
                return;
            case WitaliaPackage.CHARACTERISTIC__VALUES:
                getValues().clear();
                return;
            case WitaliaPackage.CHARACTERISTIC__MOBILE_PHONES:
                getMobilePhones().clear();
                return;
        }
        super.eUnset(featureID);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public boolean eIsSet(int featureID) {
        switch (featureID) {
            case WitaliaPackage.CHARACTERISTIC__NAME:
                return NAME_EDEFAULT == null ? name != null : !NAME_EDEFAULT.equals(name);
            case WitaliaPackage.CHARACTERISTIC__TYPE:
                return type != TYPE_EDEFAULT;
            case WitaliaPackage.CHARACTERISTIC__VALUES:
                return values != null && !values.isEmpty();
            case WitaliaPackage.CHARACTERISTIC__MOBILE_PHONES:
                return mobilePhones != null && !mobilePhones.isEmpty();
        }
        return super.eIsSet(featureID);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public String toString() {
        if (eIsProxy()) return super.toString();

        StringBuffer result = new StringBuffer(super.toString());
        result.append(" (name: ");
        result.append(name);
        result.append(", type: ");
        result.append(type);
        result.append(", values: ");
        result.append(values);
        result.append(')');
        return result.toString();
    }

} //CharacteristicImpl
