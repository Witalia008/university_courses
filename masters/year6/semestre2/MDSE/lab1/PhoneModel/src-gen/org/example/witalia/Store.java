/**
 */
package org.example.witalia;

import java.util.List;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EObject;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Store</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link org.example.witalia.Store#getPhones <em>Phones</em>}</li>
 * </ul>
 * </p>
 *
 * @see org.example.witalia.WitaliaPackage#getStore()
 * @model
 * @generated
 */
public interface Store extends EObject {
    /**
     * Returns the value of the '<em><b>Phones</b></em>' reference list.
     * The list contents are of type {@link org.example.witalia.MobilePhone}.
     * It is bidirectional and its opposite is '{@link org.example.witalia.MobilePhone#getStores <em>Stores</em>}'.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of the '<em>Phones</em>' reference list isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @return the value of the '<em>Phones</em>' reference list.
     * @see org.example.witalia.WitaliaPackage#getStore_Phones()
     * @see org.example.witalia.MobilePhone#getStores
     * @model opposite="stores"
     * @generated
     */
    EList<MobilePhone> getPhones();

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model unique="false" manUnique="false"
     *        annotation="http://www.eclipse.org/emf/2002/GenModel body='<%org.example.witalia.Store%> _this = this;\n<%org.eclipse.emf.common.util.EList%><<%org.example.witalia.MobilePhone%>> _phones = _this.getPhones();\nfor (final <%org.example.witalia.MobilePhone%> phone : _phones)\n{\n\t<%org.example.witalia.Manufacturer%> _manufacturer = phone.getManufacturer();\n\tboolean _equals = <%com.google.common.base.Objects%>.equal(_manufacturer, man);\n\tif (_equals)\n\t{\n\t\treturn phone;\n\t}\n}\nreturn null;'"
     * @generated
     */
    MobilePhone getByManufacturer(Manufacturer man);

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @model dataType="org.example.witalia.List<org.example.witalia.MobilePhone>" unique="false" many="false" minPriceUnique="false" maxPriceUnique="false"
     *        annotation="http://www.eclipse.org/emf/2002/GenModel body='<%java.util.List%><<%org.example.witalia.MobilePhone%>> results = <%org.eclipse.xtext.xbase.lib.CollectionLiterals%>.<<%org.example.witalia.MobilePhone%>>emptyList();\n<%org.example.witalia.Store%> _this = this;\n<%org.eclipse.emf.common.util.EList%><<%org.example.witalia.MobilePhone%>> _phones = _this.getPhones();\nfor (final <%org.example.witalia.MobilePhone%> phone : _phones)\n{\n\tboolean _and = false;\n\tdouble _price = phone.getPrice();\n\tboolean _greaterEqualsThan = (_price >= minPrice);\n\tif (!_greaterEqualsThan)\n\t{\n\t\t_and = false;\n\t} else\n\t{\n\t\tdouble _price_1 = phone.getPrice();\n\t\tboolean _lessEqualsThan = (_price_1 <= maxPrice);\n\t\t_and = (_greaterEqualsThan && _lessEqualsThan);\n\t}\n\tif (_and)\n\t{\n\t\tresults.add(phone);\n\t}\n}\nreturn <%org.eclipse.xtext.xbase.lib.IterableExtensions%>.<<%org.example.witalia.MobilePhone%>>toList(results);'"
     * @generated
     */
    List<MobilePhone> getWithinPrice(double minPrice, double maxPrice);

} // Store
