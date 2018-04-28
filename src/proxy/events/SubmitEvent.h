/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
 * Copyright 2016-2018 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SUBMITEVENT_H__
#define __SUBMITEVENT_H__


#include "common/crypto/Algorithm.h"
#include "net/JobResult.h"
#include "proxy/Error.h"
#include "proxy/events/MinerEvent.h"


class SubmitEvent : public MinerEvent
{
public:
    static inline SubmitEvent *create(Miner *miner, int64_t id, const char *jobId, const char *nonce, const char *result, const xmrig::Algorithm &algorithm)
    {
        return new (m_buf) SubmitEvent(miner, id, jobId, nonce, result, algorithm);
    }


    const xmrig::Algorithm &algorithm;
    JobResult request;


    inline bool isRejected() const override { return m_error != Error::NoError; }
    inline const char *message() const      { return Error::toString(m_error); }
    inline Error::Code error() const        { return m_error; }
    inline void reject(Error::Code error)   { m_error  = error; }


protected:
    inline SubmitEvent(Miner *miner, int64_t id, const char *jobId, const char *nonce, const char *result, const xmrig::Algorithm &algorithm)
        : MinerEvent(SubmitType, miner),
          algorithm(algorithm),
          request(id, jobId, nonce, result),
          m_error(Error::NoError)
    {}

private:
    Error::Code m_error;
};

#endif /* __SUBMITEVENT_H__ */
