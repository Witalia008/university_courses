/**
 */
package org.example.witalia.impl;

import java.util.Collection;
import java.util.Date;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.ENotificationImpl;
import org.eclipse.emf.ecore.impl.MinimalEObjectImpl;

import org.eclipse.emf.ecore.util.EObjectWithInverseResolvingEList;
import org.eclipse.emf.ecore.util.EcoreUtil;
import org.eclipse.emf.ecore.util.InternalEList;

import org.example.witalia.Characteristic;
import org.example.witalia.Manufacturer;
import org.example.witalia.MobilePhone;
import org.example.witalia.Store;
import org.example.witalia.WitaliaPackage;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Mobile Phone</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * <ul>
 *   <li>{@link org.example.witalia.impl.MobilePhoneImpl#getName <em>Name</em>}</li>
 *   <li>{@link org.example.witalia.impl.MobilePhoneImpl#getModel <em>Model</em>}</li>
 *   <li>{@link org.example.witalia.impl.MobilePhoneImpl#getPrice <em>Price</em>}</li>
 *   <li>{@link org.example.witalia.impl.MobilePhoneImpl#getRating <em>Rating</em>}</li>
 *   <li>{@link org.example.witalia.impl.MobilePhoneImpl#getReleaseDate <em>Release Date</em>}</li>
 *   <li>{@link org.example.witalia.impl.MobilePhoneImpl#getManufacturer <em>Manufacturer</em>}</li>
 *   <li>{@link org.example.witalia.impl.MobilePhoneImpl#getCharacteristics <em>Characteristics</em>}</li>
 *   <li>{@link org.example.witalia.impl.MobilePhoneImpl#getStores <em>Stores</em>}</li>
 * </ul>
 * </p>
 *
 * @generated
 */
public class MobilePhoneImpl extends MinimalEObjectImpl.Container implements MobilePhone {
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
     * The default value of the '{@link #getModel() <em>Model</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getModel()
     * @generated
     * @ordered
     */
    protected static final String MODEL_EDEFAULT = null;

    /**
     * The cached value of the '{@link #getModel() <em>Model</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getModel()
     * @generated
     * @ordered
     */
    protected String model = MODEL_EDEFAULT;

    /**
     * The default value of the '{@link #getPrice() <em>Price</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPrice()
     * @generated
     * @ordered
     */
    protected static final double PRICE_EDEFAULT = 0.0;

    /**
     * The cached value of the '{@link #getPrice() <em>Price</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPrice()
     * @generated
     * @ordered
     */
    protected double price = PRICE_EDEFAULT;

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
     * The default value of the '{@link #getReleaseDate() <em>Release Date</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getReleaseDate()
     * @generated
     * @ordered
     */
    protected static final Date RELEASE_DATE_EDEFAULT = null;

    /**
     * The cached value of the '{@link #getReleaseDate() <em>Release Date</em>}' attribute.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getReleaseDate()
     * @generated
     * @ordered
     */
    protected Date releaseDate = RELEASE_DATE_EDEFAULT;

    /**
     * The cached value of the '{@link #getCharacteristics() <em>Characteristics</em>}' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getCharacteristics()
     * @generated
     * @ordered
     */
    protected EList<Characteristic> characteristics;

    /**
     * The cached value of the '{@link #getStores() <em>Stores</em>}' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getStores()
     * @generated
     * @ordered
     */
    protected EList<Store> stores;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected MobilePhoneImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return WitaliaPackage.Literals.MOBILE_PHONE;
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
            eNotify(new ENotificationImpl(this, Notification.SET, WitaliaPackage.MOBILE_PHONE__NAME, oldName, name));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public String getModel() {
        return model;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setModel(String newModel) {
        String oldModel = model;
        model = newModel;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET, WitaliaPackage.MOBILE_PHONE__MODEL, oldModel, model));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public double getPrice() {
        return price;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setPrice(double newPrice) {
        double oldPrice = price;
        price = newPrice;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET, WitaliaPackage.MOBILE_PHONE__PRICE, oldPrice, price));
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
            eNotify(new ENotificationImpl(this, Notification.SET, WitaliaPackage.MOBILE_PHONE__RATING, oldRating, rating));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public Date getReleaseDate() {
        return releaseDate;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setReleaseDate(Date newReleaseDate) {
        Date oldReleaseDate = releaseDate;
        releaseDate = newReleaseDate;
        if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET, WitaliaPackage.MOBILE_PHONE__RELEASE_DATE, oldReleaseDate, releaseDate));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public Manufacturer getManufacturer() {
        if (eContainerFeatureID() != WitaliaPackage.MOBILE_PHONE__MANUFACTURER) return null;
        return (Manufacturer)eInternalContainer();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public NotificationChain basicSetManufacturer(Manufacturer newManufacturer, NotificationChain msgs) {
        msgs = eBasicSetContainer((InternalEObject)newManufacturer, WitaliaPackage.MOBILE_PHONE__MANUFACTURER, msgs);
        return msgs;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public void setManufacturer(Manufacturer newManufacturer) {
        if (newManufacturer != eInternalContainer() || (eContainerFeatureID() != WitaliaPackage.MOBILE_PHONE__MANUFACTURER && newManufacturer != null)) {
            if (EcoreUtil.isAncestor(this, newManufacturer))
                throw new IllegalArgumentException("Recursive containment not allowed for " + toString());
            NotificationChain msgs = null;
            if (eInternalContainer() != null)
                msgs = eBasicRemoveFromContainer(msgs);
            if (newManufacturer != null)
                msgs = ((InternalEObject)newManufacturer).eInverseAdd(this, WitaliaPackage.MANUFACTURER__MOBILE_PHONES, Manufacturer.class, msgs);
            msgs = basicSetManufacturer(newManufacturer, msgs);
            if (msgs != null) msgs.dispatch();
        }
        else if (eNotificationRequired())
            eNotify(new ENotificationImpl(this, Notification.SET, WitaliaPackage.MOBILE_PHONE__MANUFACTURER, newManufacturer, newManufacturer));
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<Characteristic> getCharacteristics() {
        if (characteristics == null) {
            characteristics = new EObjectWithInverseResolvingEList.ManyInverse<Characteristic>(Characteristic.class, this, WitaliaPackage.MOBILE_PHONE__CHARACTERISTICS, WitaliaPackage.CHARACTERISTIC__MOBILE_PHONES);
        }
        return characteristics;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<Store> getStores() {
        if (stores == null) {
            stores = new EObjectWithInverseResolvingEList.ManyInverse<Store>(Store.class, this, WitaliaPackage.MOBILE_PHONE__STORES, WitaliaPackage.STORE__PHONES);
        }
        return stores;
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
            case WitaliaPackage.MOBILE_PHONE__MANUFACTURER:
                if (eInternalContainer() != null)
                    msgs = eBasicRemoveFromContainer(msgs);
                return basicSetManufacturer((Manufacturer)otherEnd, msgs);
            case WitaliaPackage.MOBILE_PHONE__CHARACTERISTICS:
                return ((InternalEList<InternalEObject>)(InternalEList<?>)getCharacteristics()).basicAdd(otherEnd, msgs);
            case WitaliaPackage.MOBILE_PHONE__STORES:
                return ((InternalEList<InternalEObject>)(InternalEList<?>)getStores()).basicAdd(otherEnd, msgs);
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
            case WitaliaPackage.MOBILE_PHONE__MANUFACTURER:
                return basicSetManufacturer(null, msgs);
            case WitaliaPackage.MOBILE_PHONE__CHARACTERISTICS:
                return ((InternalEList<?>)getCharacteristics()).basicRemove(otherEnd, msgs);
            case WitaliaPackage.MOBILE_PHONE__STORES:
                return ((InternalEList<?>)getStores()).basicRemove(otherEnd, msgs);
        }
        return super.eInverseRemove(otherEnd, featureID, msgs);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public NotificationChain eBasicRemoveFromContainerFeature(NotificationChain msgs) {
        switch (eContainerFeatureID()) {
            case WitaliaPackage.MOBILE_PHONE__MANUFACTURER:
                return eInternalContainer().eInverseRemove(this, WitaliaPackage.MANUFACTURER__MOBILE_PHONES, Manufacturer.class, msgs);
        }
        return super.eBasicRemoveFromContainerFeature(msgs);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eGet(int featureID, boolean resolve, boolean coreType) {
        switch (featureID) {
            case WitaliaPackage.MOBILE_PHONE__NAME:
                return getName();
            case WitaliaPackage.MOBILE_PHONE__MODEL:
                return getModel();
            case WitaliaPackage.MOBILE_PHONE__PRICE:
                return getPrice();
            case WitaliaPackage.MOBILE_PHONE__RATING:
                return getRating();
            case WitaliaPackage.MOBILE_PHONE__RELEASE_DATE:
                return getReleaseDate();
            case WitaliaPackage.MOBILE_PHONE__MANUFACTURER:
                return getManufacturer();
            case WitaliaPackage.MOBILE_PHONE__CHARACTERISTICS:
                return getCharacteristics();
            case WitaliaPackage.MOBILE_PHONE__STORES:
                return getStores();
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
            case WitaliaPackage.MOBILE_PHONE__NAME:
                setName((String)newValue);
                return;
            case WitaliaPackage.MOBILE_PHONE__MODEL:
                setModel((String)newValue);
                return;
            case WitaliaPackage.MOBILE_PHONE__PRICE:
                setPrice((Double)newValue);
                return;
            case WitaliaPackage.MOBILE_PHONE__RATING:
                setRating((Integer)newValue);
                return;
            case WitaliaPackage.MOBILE_PHONE__RELEASE_DATE:
                setReleaseDate((Date)newValue);
                return;
            case WitaliaPackage.MOBILE_PHONE__MANUFACTURER:
                setManufacturer((Manufacturer)newValue);
                return;
            case WitaliaPackage.MOBILE_PHONE__CHARACTERISTICS:
                getCharacteristics().clear();
                getCharacteristics().addAll((Collection<? extends Characteristic>)newValue);
                return;
            case WitaliaPackage.MOBILE_PHONE__STORES:
                getStores().clear();
                getStores().addAll((Collection<? extends Store>)newValue);
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
            case WitaliaPackage.MOBILE_PHONE__NAME:
                setName(NAME_EDEFAULT);
                return;
            case WitaliaPackage.MOBILE_PHONE__MODEL:
                setModel(MODEL_EDEFAULT);
                return;
            case WitaliaPackage.MOBILE_PHONE__PRICE:
                setPrice(PRICE_EDEFAULT);
                return;
            case WitaliaPackage.MOBILE_PHONE__RATING:
                setRating(RATING_EDEFAULT);
                return;
            case WitaliaPackage.MOBILE_PHONE__RELEASE_DATE:
                setReleaseDate(RELEASE_DATE_EDEFAULT);
                return;
            case WitaliaPackage.MOBILE_PHONE__MANUFACTURER:
                setManufacturer((Manufacturer)null);
                return;
            case WitaliaPackage.MOBILE_PHONE__CHARACTERISTICS:
                getCharacteristics().clear();
                return;
            case WitaliaPackage.MOBILE_PHONE__STORES:
                getStores().clear();
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
            case WitaliaPackage.MOBILE_PHONE__NAME:
                return NAME_EDEFAULT == null ? name != null : !NAME_EDEFAULT.equals(name);
            case WitaliaPackage.MOBILE_PHONE__MODEL:
                return MODEL_EDEFAULT == null ? model != null : !MODEL_EDEFAULT.equals(model);
            case WitaliaPackage.MOBILE_PHONE__PRICE:
                return price != PRICE_EDEFAULT;
            case WitaliaPackage.MOBILE_PHONE__RATING:
                return rating != RATING_EDEFAULT;
            case WitaliaPackage.MOBILE_PHONE__RELEASE_DATE:
                return RELEASE_DATE_EDEFAULT == null ? releaseDate != null : !RELEASE_DATE_EDEFAULT.equals(releaseDate);
            case WitaliaPackage.MOBILE_PHONE__MANUFACTURER:
                return getManufacturer() != null;
            case WitaliaPackage.MOBILE_PHONE__CHARACTERISTICS:
                return characteristics != null && !characteristics.isEmpty();
            case WitaliaPackage.MOBILE_PHONE__STORES:
                return stores != null && !stores.isEmpty();
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
        result.append(", model: ");
        result.append(model);
        result.append(", price: ");
        result.append(price);
        result.append(", rating: ");
        result.append(rating);
        result.append(", releaseDate: ");
        result.append(releaseDate);
        result.append(')');
        return result.toString();
    }

} //MobilePhoneImpl
