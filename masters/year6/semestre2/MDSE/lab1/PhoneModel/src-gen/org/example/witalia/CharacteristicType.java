/**
 */
package org.example.witalia;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import org.eclipse.emf.common.util.Enumerator;

/**
 * <!-- begin-user-doc -->
 * A representation of the literals of the enumeration '<em><b>Characteristic Type</b></em>',
 * and utility methods for working with them.
 * <!-- end-user-doc -->
 * @see org.example.witalia.WitaliaPackage#getCharacteristicType()
 * @model
 * @generated
 */
public enum CharacteristicType implements Enumerator {
    /**
     * The '<em><b>Hardware</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #HARDWARE_VALUE
     * @generated
     * @ordered
     */
    HARDWARE(0, "Hardware", "HARD"),

    /**
     * The '<em><b>Software</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #SOFTWARE_VALUE
     * @generated
     * @ordered
     */
    SOFTWARE(0, "Software", "SOFT"),

    /**
     * The '<em><b>Support</b></em>' literal object.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @see #SUPPORT_VALUE
     * @generated
     * @ordered
     */
    SUPPORT(0, "Support", "SUPP");

    /**
     * The '<em><b>Hardware</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Hardware</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #HARDWARE
     * @model name="Hardware" literal="HARD"
     * @generated
     * @ordered
     */
    public static final int HARDWARE_VALUE = 0;

    /**
     * The '<em><b>Software</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Software</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #SOFTWARE
     * @model name="Software" literal="SOFT"
     * @generated
     * @ordered
     */
    public static final int SOFTWARE_VALUE = 0;

    /**
     * The '<em><b>Support</b></em>' literal value.
     * <!-- begin-user-doc -->
     * <p>
     * If the meaning of '<em><b>Support</b></em>' literal object isn't clear,
     * there really should be more of a description here...
     * </p>
     * <!-- end-user-doc -->
     * @see #SUPPORT
     * @model name="Support" literal="SUPP"
     * @generated
     * @ordered
     */
    public static final int SUPPORT_VALUE = 0;

    /**
     * An array of all the '<em><b>Characteristic Type</b></em>' enumerators.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private static final CharacteristicType[] VALUES_ARRAY =
        new CharacteristicType[] {
            HARDWARE,
            SOFTWARE,
            SUPPORT,
        };

    /**
     * A public read-only list of all the '<em><b>Characteristic Type</b></em>' enumerators.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static final List<CharacteristicType> VALUES = Collections.unmodifiableList(Arrays.asList(VALUES_ARRAY));

    /**
     * Returns the '<em><b>Characteristic Type</b></em>' literal with the specified literal value.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static CharacteristicType get(String literal) {
        for (int i = 0; i < VALUES_ARRAY.length; ++i) {
            CharacteristicType result = VALUES_ARRAY[i];
            if (result.toString().equals(literal)) {
                return result;
            }
        }
        return null;
    }

    /**
     * Returns the '<em><b>Characteristic Type</b></em>' literal with the specified name.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static CharacteristicType getByName(String name) {
        for (int i = 0; i < VALUES_ARRAY.length; ++i) {
            CharacteristicType result = VALUES_ARRAY[i];
            if (result.getName().equals(name)) {
                return result;
            }
        }
        return null;
    }

    /**
     * Returns the '<em><b>Characteristic Type</b></em>' literal with the specified integer value.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public static CharacteristicType get(int value) {
        switch (value) {
            case HARDWARE_VALUE: return HARDWARE;
        }
        return null;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private final int value;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private final String name;

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private final String literal;

    /**
     * Only this class can construct instances.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    private CharacteristicType(int value, String name, String literal) {
        this.value = value;
        this.name = name;
        this.literal = literal;
    }

    /**
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    public int getValue() {
      return value;
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
    public String getLiteral() {
      return literal;
    }

    /**
     * Returns the literal value of the enumerator, which is its string representation.
     * <!-- begin-user-doc -->
     * <!-- end-user-doc -->
     * @generated
     */
    @Override
    public String toString() {
        return literal;
    }
    
} //CharacteristicType
