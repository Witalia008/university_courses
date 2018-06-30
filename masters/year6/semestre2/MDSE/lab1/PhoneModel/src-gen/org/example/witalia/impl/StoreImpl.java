/**
 */
package org.example.witalia.impl;

import com.google.common.base.Objects;

import java.lang.reflect.InvocationTargetException;

import java.util.Collection;
import java.util.List;

import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.impl.MinimalEObjectImpl;

import org.eclipse.emf.ecore.util.EObjectWithInverseResolvingEList;
import org.eclipse.emf.ecore.util.InternalEList;

import org.eclipse.xtext.xbase.lib.CollectionLiterals;
import org.eclipse.xtext.xbase.lib.IterableExtensions;

import org.example.witalia.Manufacturer;
import org.example.witalia.MobilePhone;
import org.example.witalia.Store;
import org.example.witalia.WitaliaPackage;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Store</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * <ul>
 *   <li>{@link org.example.witalia.impl.StoreImpl#getPhones <em>Phones</em>}</li>
 * </ul>
 * </p>
 *
 * @generated
 */
public class StoreImpl extends MinimalEObjectImpl.Container implements Store {
    /**
     * The cached value of the '{@link #getPhones() <em>Phones</em>}' reference list.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #getPhones()
     * @generated
     * @ordered
     */
    protected EList<MobilePhone> phones;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    protected StoreImpl() {
        super();
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    protected EClass eStaticClass() {
        return WitaliaPackage.Literals.STORE;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public EList<MobilePhone> getPhones() {
        if (phones == null) {
            phones = new EObjectWithInverseResolvingEList.ManyInverse<MobilePhone>(MobilePhone.class, this, WitaliaPackage.STORE__PHONES, WitaliaPackage.MOBILE_PHONE__STORES);
        }
        return phones;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public MobilePhone getByManufacturer(final Manufacturer man) {
        Store _this = this;
        EList<MobilePhone> _phones = _this.getPhones();
        for (final MobilePhone phone : _phones) {
            Manufacturer _manufacturer = phone.getManufacturer();
            boolean _equals = Objects.equal(_manufacturer, man);
            if (_equals) {
                return phone;
            }
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public List<MobilePhone> getWithinPrice(final double minPrice, final double maxPrice) {
        List<MobilePhone> results = CollectionLiterals.<MobilePhone>emptyList();
        Store _this = this;
        EList<MobilePhone> _phones = _this.getPhones();
        for (final MobilePhone phone : _phones) {
            boolean _and = false;
            double _price = phone.getPrice();
            boolean _greaterEqualsThan = (_price >= minPrice);
            if (!_greaterEqualsThan) {
                _and = false;
            } else {
                double _price_1 = phone.getPrice();
                boolean _lessEqualsThan = (_price_1 <= maxPrice);
                _and = (_greaterEqualsThan && _lessEqualsThan);
            }
            if (_and) {
                results.add(phone);
            }
        }
        return IterableExtensions.<MobilePhone>toList(results);
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
            case WitaliaPackage.STORE__PHONES:
                return ((InternalEList<InternalEObject>)(InternalEList<?>)getPhones()).basicAdd(otherEnd, msgs);
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
            case WitaliaPackage.STORE__PHONES:
                return ((InternalEList<?>)getPhones()).basicRemove(otherEnd, msgs);
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
            case WitaliaPackage.STORE__PHONES:
                return getPhones();
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
            case WitaliaPackage.STORE__PHONES:
                getPhones().clear();
                getPhones().addAll((Collection<? extends MobilePhone>)newValue);
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
            case WitaliaPackage.STORE__PHONES:
                getPhones().clear();
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
            case WitaliaPackage.STORE__PHONES:
                return phones != null && !phones.isEmpty();
        }
        return super.eIsSet(featureID);
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public Object eInvoke(int operationID, EList<?> arguments) throws InvocationTargetException {
        switch (operationID) {
            case WitaliaPackage.STORE___GET_BY_MANUFACTURER__MANUFACTURER:
                return getByManufacturer((Manufacturer)arguments.get(0));
            case WitaliaPackage.STORE___GET_WITHIN_PRICE__DOUBLE_DOUBLE:
                return getWithinPrice((Double)arguments.get(0), (Double)arguments.get(1));
        }
        return super.eInvoke(operationID, arguments);
    }

} //StoreImpl
