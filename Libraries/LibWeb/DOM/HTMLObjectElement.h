/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <LibCore/Forward.h>
#include <LibGfx/Forward.h>
#include <LibWeb/DOM/HTMLElement.h>
#include <LibWeb/Loader/ImageLoader.h>

namespace Web {

class LayoutDocument;

class HTMLObjectElement final : public HTMLElement {
public:
    HTMLObjectElement(Document&, const FlyString& tag_name);
    virtual ~HTMLObjectElement() override;

    virtual void parse_attribute(const FlyString& name, const String& value) override;

    String data() const { return attribute(HTML::AttributeNames::data); }
    String type() const { return attribute(HTML::AttributeNames::type); }

private:
    virtual RefPtr<LayoutNode> create_layout_node(const StyleProperties* parent_style) override;

    ImageLoader m_image_loader;
    bool m_should_show_fallback_content { false };
};

template<>
inline bool is<HTMLObjectElement>(const Node& node)
{
    return is<Element>(node) && to<Element>(node).tag_name() == HTML::TagNames::object;
}

}
