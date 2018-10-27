/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBBITCOIN_CHAIN_PAYMENT_RECORD_HPP
#define LIBBITCOIN_CHAIN_PAYMENT_RECORD_HPP

#include <cstddef>
#include <cstdint>
#include <istream>
#include <vector>
#include <bitcoin/bitcoin/constants.hpp>
#include <bitcoin/bitcoin/define.hpp>
#include <bitcoin/bitcoin/utility/data.hpp>
#include <bitcoin/bitcoin/utility/reader.hpp>
#include <bitcoin/bitcoin/utility/writer.hpp>

namespace libbitcoin {
namespace chain {

/// This class models blockchain storage of a payment record.
class BC_API payment_record
{
public:
    typedef std::vector<payment_record> list;

    // Constructors.
    //-------------------------------------------------------------------------

    payment_record();

    payment_record(chain::payment_record&& other);
    payment_record(const chain::payment_record& other);

    payment_record(uint64_t link, uint32_t index, uint64_t data, bool output);

    // Operators.
    //-------------------------------------------------------------------------

    payment_record& operator=(payment_record&& other);
    payment_record& operator=(const payment_record& other);

    bool operator==(const payment_record& other) const;
    bool operator!=(const payment_record& other) const;

    // Deserialization.
    //-------------------------------------------------------------------------

    static payment_record factory(const data_chunk& data, bool wire=true);
    static payment_record factory(std::istream& stream, bool wire=true);
    static payment_record factory(reader& source, bool wire=true);

    bool from_data(const data_chunk& data, bool wire=true);
    bool from_data(std::istream& stream, bool wire=true);
    bool from_data(reader& source, bool wire=true);

    bool is_valid() const;

    // Serialization.
    //-------------------------------------------------------------------------

    data_chunk to_data(bool wire=true) const;
    void to_data(std::ostream& stream, bool wire=true) const;
    void to_data(writer& sink, bool wire=true) const;

    // Properties (size, accessors).
    //-------------------------------------------------------------------------

    static size_t satoshi_fixed_size(bool wire=true);
    size_t serialized_size(bool wire=true) const;

    /// The point is an output.
    bool is_output() const;

    /// The value of the input point or checksum of the output point.
    uint64_t data() const;

    /// The blockchain height of the point.
    uint64_t link() const;

    /// The blockchain height of the point.
    size_t height() const;

    /// Set the point height.
    void set_height(size_t height);

    /// The hash of the point.
    hash_digest hash() const;

    /// Set the point hash.
    void set_hash(hash_digest&& hash);

    /// The index of the point.
    uint32_t index() const;

    /// Set the point index.
    void set_index(uint32_t value);

protected:
    void reset();

private:
    bool valid_;
    bool output_;
    size_t height_;
    hash_digest hash_;
    uint32_t index_;
    uint64_t data_;
    uint64_t link_;
};

} // namespace chain
} // namespace libbitcoin

#endif
