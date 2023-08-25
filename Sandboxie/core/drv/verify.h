/*
 * Copyright (C) 2021-2023 David Xanatos, xanasoft.com
 *
 * Process Hacker is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Process Hacker is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Process Hacker.  If not, see <http://www.gnu.org/licenses/>.
 */

#define SOFTWARE_NAME L"Sandboxie-Plus"

typedef union _SCertInfo {
    unsigned long long State;
    struct {
        unsigned long
            active    : 1,      // certificate is active
            expired   : 1,      // certificate is expired but may be active
            outdated  : 1,      // certificate is expired, not anymore valid for the current build
            unused_1  : 2,      // DEPRECATED
            grace_period: 1,    // the certificate is expired and or outdated but we keep it valid for 1 extra month to allof wor a seamless renewal
            reservd_2 : 2,

            type      : 5,
            level     : 3,

            reservd_3 : 8,

            reservd_4 : 8;

        unsigned long expirers_in_sec;
    };
} SCertInfo;

enum ECertType {
    eCertNoType         = 0b00000,

    eCertEternal        = 0b00100,
    eCertContributor    = 0b00101,
//  eCert               = 0b00110,
//  eCert               = 0b00111,
            
    eCertBusiness       = 0b01000,
//  eCert               = 0b01001,
//  eCert               = 0b01010,
//  eCert               = 0b01011,

    eCertPersonal       = 0b01100,
//  eCert               = 0b01101, 
//  eCert               = 0b01110,
//  eCert               = 0b01111,

    eCertSubscription   = 0b10000,
    eCertFamily         = 0b10001, 
//  eCert               = 0b10010,
//  eCert               = 0b10011,
            
//  eCertOther          = 0b10100,
//  eCert               = 0b10101, 
//  eCert               = 0b10110,
//  eCert               = 0b10111,

    eCertPatreon        = 0b11000,
    eCertGreatPatreon   = 0b11001,
    eCertEntryPatreon   = 0b11010,
//  eCert               = 0b11011,

    eCertEvaluation     = 0b11100
};
        
enum ECertLevel {
    eCertNoLevel        = 0b000,
    eCertStandard       = 0b010,
    eCertAdvanced       = 0b100,
    eCertMaxLevel       = 0b111,
};

#define CERT_IS_TYPE(cert,t)        ((cert.type & 0b11100) == (unsigned long)(t))
#define CERT_IS_SUBSCRIPTION(cert)  (CERT_IS_TYPE(cert, eCertBusiness) || CERT_IS_TYPE(cert, eCertSubscription) || cert.type == eCertEntryPatreon || CERT_IS_TYPE(cert, eCertEvaluation))
#define CERT_IS_INSIDER(cert)		(CERT_IS_TYPE(cert, eCertEternal) || cert.type == eCertGreatPatreon)
#define CERT_IS_LEVEL(cert,l)       (cert.active && cert.level >= (unsigned long)(l))

#ifdef KERNEL_MODE
extern SCertInfo Verify_CertInfo;
#endif