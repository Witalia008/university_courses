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

import org.eclipse.emf.ecore.util.EObjectContainmentWithInverseEList;
import org.eclipse.emf.ecore.util.InternalEList;

import org.example.witalia.Manufacturer;
import org.example.witalia.MobilePhone;
import org.example.witalia.WitaliaPackage;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Manufacturer</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * <ul>
 *   <li>{@link org.example.witalia.impl.ManufacturerImpl#getName <em>Name</em>}</li>
 *   <li>{@link org.example.witalia.impl.ManufacturerImpl#getAddress <em>Address</em>}</li>
 *   <li>{@link org.example.witalia.impl.ManufacturerImpl#getPhone <em>Phone</em>}</li>
 *   <li>{@link org.example.witalia.impl.ManufacturerImpl#getRating <em>Rating</em>}</li>
 *   <li>{@link org.example.witalia.impl.ManufacturerImpl#getMobilePhones <em>Mobile Phones</em>}</li>
 * </ul>
 * </p>
 *
 * @generated
 */
public class ManufacturerImpl extends MinimalEObjectImpl.Container implements Manufacturer {
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
     * The default value of the '{@link #getAddress() <em>Address</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getAddress()
     * @generated
     * @ordered
     */
    protected static final String ADDRESS_EDEFAULT = null;

    /**
     * The cached value of the '{@link #getAddress() <em>Address</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getAddress()
     * @generated
     * @ordered
     */
    protected String address = ADDRESS_EDEFAULT;

    /**
     * The default value of the '{@link #getPhone() <em>Phone</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPhone()
     * @generated
     * @ordered
     */
    protected static final String PHONE_EDEFAULT = null;

    /**
     * The cached value of the '{@link #getPhone() <em>Phone</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPhone()
     * @generated
     * @ordered
     */
    protected String phone = PHONE_EDEFAULT;

    /**
     * The default value of the '{@link #getRating() <em>Rating</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getRating()
     * @generated
     * @ordered
     */
    protected static final int RATING_EDEFAULT = 0;

    /**
     * The cached value of the '{@link #getRating() <em>Rating</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getRating()
     * @generated
     * @ordered
     */
    protected int rating = RATING_EDEFAULT;

    /**
     * The cached value of the '{@link #getMobilePhones() <em>Mobile Phones</em>}' containment reference list.
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
    protected ManufacturerImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return WitaliaPackage.Literals.MANUFACTURER;
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
            eNotify(new ENotificationImpl(this, Notification.SET, WitaliaPackage.MANUFACTURER__NAME, oldName, name));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public String getAddress() {
        return address;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setAddress(String newAddress) {
        String oldAddress = address;
        address = newAddress;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET, WitaliaPackage.MANUFACTURER__ADDRESS, oldAddress, address));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public String getPhone() {
        return phone;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setPhone(String newPhone) {
        String oldPhone = phone;
        phone = newPhone;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET, WitaliaPackage.MANUFACTURER__PHONE, oldPhone, phone));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public int getRating() {
        return rating;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setRating(int newRating) {
        int oldRating = rating;
        rating = newRating;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET, WitaliaPackage.MANUFACTURER__RATING, oldRating, rating));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<MobilePhone> getMobilePhones() {
        if (mobilePhones == null) {
            mobilePhones = new EObjectContainmentWithInverseEList<MobilePhone>(MobilePhone.class, this, WitaliaPackage.MANUFACTURER__MOBILE_PHONES, WitaliaPackage.MOBILE_PHONE__MANUFACTURER);
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
            case WitaliaPackage.MANUFACTURER__MOBILE_PHONES:
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
            case WitaliaPackage.MANUFACTURER__MOBILE_PHONES:
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
            case WitaliaPackage.MANUFACTURER__NAME:
                return getName();
            case WitaliaPackage.MANUFACTURER__ADDRESS:
                return getAddress();
            case WitaliaPackage.MANUFACTURER__PHONE:
                return getPhone();
            case WitaliaPackage.MANUFACTURER__RATING:
                return getRating();
            case WitaliaPackage.MANUFACTURER__MOBILE_PHONES:
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
            case WitaliaPackage.MANUFACTURER__NAME:
                setName((String)newValue);
                return;
            case WitaliaPackage.MANUFACTURER__ADDRESS:
                setAddress((String)newValue);
                return;
            case WitaliaPackage.MANUFACTURER__PHONE:
                setPhone((String)newValue);
                return;
            case WitaliaPackage.MANUFACTURER__RATING:
                setRating((Integer)newValue);
                return;
            case WitaliaPackage.MANUFACTURER__MOBILE_PHONES:
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
            case WitaliaPackage.MANUFACTURER__NAME:
                setName(NAME_EDEFAULT);
                return;
            case WitaliaPackage.MANUFACTURER__ADDRESS:
                setAddress(ADDRESS_EDEFAULT);
                return;
            case WitaliaPackage.MANUFACTURER__PHONE:
                setPhone(PHONE_EDEFAULT);
                return;
            case WitaliaPackage.MANUFACTURER__RATING:
                setRating(RATING_EDEFAULT);
                return;
            case WitaliaPackage.MANUFACTURER__MOBILE_PHONES:
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
            case WitaliaPackage.MANUFACTURER__NAME:
                return NAME_EDEFAULT == null ? name != null : !NAME_EDEFAULT.equals(name);
            case WitaliaPackage.MANUFACTURER__ADDRESS:
                return ADDRESS_EDEFAULT == null ? address != null : !ADDRESS_EDEFAULT.equals(address);
            case WitaliaPackage.MANUFACTURER__PHONE:
                return PHONE_EDEFAULT == null ? phone != null : !PHONE_EDEFAULT.equals(phone);
            case WitaliaPackage.MANUFACTURER__RATING:
                return rating != RATING_EDEFAULT;
            case WitaliaPackage.MANUFACTURER__MOBILE_PHONES:
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
        result.append(", address: ");
        result.append(address);
        result.append(", phone: ");
        result.append(phone);
        result.append(", rating: ");
        result.append(rating);
        result.append(')');
        return result.toString();
    }

} //ManufacturerImpl
