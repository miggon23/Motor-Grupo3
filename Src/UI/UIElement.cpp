#include "UIElement.h"
#include "CEGUI/CEGUI.h"
#include "CEGUI/Event.h"
#include "CEGUI/EventArgs.h"
#include "CEGUI/ImageManager.h"
#include "CEGUI/Window.h"
#include "CEGUI/WindowRenderer.h"
#include "CEGUI/widgets/PushButton.h"
#include "ECS/Manager.h"
#include "FlamingoUtils/SQuaternion.h"
#include "FlamingoUtils/SVector2.h"
#include "FlamingoUtils/SVector3.h"
#include "UISystem.h"
#include <iostream>

#include "Scripting/BehaviourScript.h"

namespace Flamingo
{
    UIElement::UIElement()
    {
        m_element = nullptr;
        m_uiSys = nullptr;
    }

    UIElement::~UIElement()
    {
    }

    void UIElement::initComponent()
    {
        try
        {
            m_uiSys = Manager::instance()->getSystem<Flamingo::UISystem>();
            m_element = nullptr;
            if (Manager::instance()->getComponent<Transform>(m_ent) == nullptr)
            {
                throw std::runtime_error(m_ent->getName() + "Add Transform component to set uiElement Component\n");
            }
            //createEmptyWindow("");

            setElementWidget(m_type, m_name);

            auto t = m_mngr->getComponent<Transform>(m_ent);
            t->setPosition({t->getPosition().getX(), t->getPosition().getY(), 0});
            t->setScale({t->getScale().getX(), t->getScale().getY(), 0});
            setText(m_text);

            if (m_type == "FlamingoDefaultUI/StaticImage")
            {
                m_element->moveToBack();

                setImage("Image", m_name, m_image);
                m_element->setDisabled(true);
            }
            else if (m_image != "" && m_type == "FlamingoDefaultUI/ImageButton")
            {
                setImage("NormalImage", m_name, m_image);
                setImage("HoverImage", m_name, m_image);
                setImage("PushedImage", m_name, m_image);
                setImage("DisabledImage", m_name, m_image);

                m_element->moveToFront();
            }
        }
        catch (...)
        {
            throw std::exception("[UI ERROR]: Invalid params in element");
        }
    }

    void UIElement::initValues(std::string type, std::string name, std::string text, const std::string image)
    {
        m_type = type;
        m_name = name;
        m_text = text;
        m_image = image;
    }

    void UIElement::setText(const std::string& text)
    {
        if (m_element == nullptr)return;
        m_element->setText(text);
    }

    void UIElement::setAlpha(float alpha)
    {
        if (m_element == nullptr)return;
        m_element->setAlpha(alpha);
    }

    void UIElement::setActive(bool valor)
    {
        if (m_element == nullptr) return;

        if (valor)
            m_element->activate();
        else
            m_element->deactivate();
    }

    bool UIElement::isActive()
    {
        if (m_element == nullptr)return false;

        return m_element->isActive();
    }

    void UIElement::addChild(Flamingo::UIElement* element)
    {
        if (m_element == nullptr)return;

        m_element->addChild(element->getWindowElement());
        childs[element->m_element->getName().c_str()] = element;
    }

    Flamingo::UIElement* UIElement::getChild(const std::string& childName)
    {
        for (auto it : childs)
            if (it.first == childName)
                return it.second;
        return nullptr;
    }

    void UIElement::setPosition(SVector3 pos)
    {
        if (m_element != nullptr)
            m_element->setPosition(CEGUI::UVector2(CEGUI::UDim(pos.getX(), 0), CEGUI::UDim(pos.getY(), 0)));
    }

    SVector2 UIElement::GetPosition()
    {
        if (m_element == nullptr)return SVector2();

        return SVector2(m_element->getPosition().d_x.d_scale, m_element->getPosition().d_y.d_scale);
    }

    void UIElement::setSize(SVector3 size)
    {
        if (m_element != nullptr)
            m_element->setSize(CEGUI::USize(CEGUI::UDim(0, size.getX()), CEGUI::UDim(0, size.getY())));
    }

    void UIElement::setRotation(SQuaternion rot)
    {
        if (m_element != nullptr)
            m_element->setRotation(rot);
    }

    Flamingo::SVector2 UIElement::getPivotCenter()
    {
        if (m_element == nullptr)return SVector2();

        float i = m_element->getOuterRectClipper().d_min.d_x;
        float j = m_element->getOuterRectClipper().d_max.d_x;

        float w = m_element->getOuterRectClipper().d_min.d_y;
        float k = m_element->getOuterRectClipper().d_max.d_y;

        return Flamingo::SVector2((i + j) / 2, (w + k) / 2);
    }

    CEGUI::Window* UIElement::getWindowElement()
    {
        return m_element;
    }

    void UIElement::setElement(CEGUI::Window* element)
    {
        if (m_element != nullptr)
            m_element->destroy();
        m_element = element;
    }

    void UIElement::setToInitComponent()
    {
        auto transform = m_mngr->getComponent<Transform>(m_ent);
        setPosition(transform->getPosition());
        setSize(transform->getScale());
        setRotation(transform->getRotation());
    }

    void UIElement::setNewParent(CEGUI::Window* wnd)
    {
        for (auto it : childs)
            wnd->addChild(it.second->getWindowElement());

        if (m_element != nullptr)
            m_element->destroy();
        m_element = wnd;
    }

    void UIElement::setElementWidget(const std::string& widget, const std::string& name)
    {
        if (m_uiSys == nullptr)
            m_uiSys = m_mngr->getSystem<Flamingo::UISystem>();
        setNewParent(m_uiSys->createWidget(widget, name));
        setToInitComponent();
    }

    void UIElement::createEmptyWindow(const std::string& name)
    {
        if (m_uiSys == nullptr)
            m_uiSys = m_mngr->getSystem<Flamingo::UISystem>();
        setNewParent(m_uiSys->createEmptyWindow(name));
        setToInitComponent();
    }

    void UIElement::setAxisAligment(bool set)
    {
        if (m_element == nullptr)return;

        m_element->setPixelAligned(set);
    }

    void UIElement::setImage(const std::string& property, const std::string& name, const std::string& file)
    {
        if (m_element == nullptr)return;

        if (!CEGUI::ImageManager::getSingleton().isDefined(name))
        {
            // memory leaks procedentes de CEGUI al a�adir una imagen a su banco, llamamos los destroy mas tarde pero nada
            CEGUI::ImageManager::getSingleton().addFromImageFile(name, file);
        }
        setProperty(property, name);
    }

    void UIElement::setProperty(const std::string& property, const std::string& file)
    {
        if (m_element == nullptr)return;
        try
        {
            m_element->setProperty(property, file);
        }
        catch (const std::exception&)
        {
            throw std::runtime_error("Propiedad" + property + "no compatible con este elemento");
        }
    }

    void UIElement::subsEvent(BehaviourScript* t_s)
    {
        if (m_element != nullptr)
        {
            m_element->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&BehaviourScript::clickFuntion, t_s));
        }
    }
} // namespace Flamingo