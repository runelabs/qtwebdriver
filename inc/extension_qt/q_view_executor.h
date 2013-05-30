#ifndef WEBDRIVER_Q_VIEW_EXECUTOR_H
#define WEBDRIVER_Q_VIEW_EXECUTOR_H

#include <string>
#include <vector>
#include <map>

#include "webdriver_view_executor.h"

#include "webdriver_error.h"

#include <QtGui/QWidget>

namespace webdriver {

#define NOT_SUPPORTED_IMPL      {*error = new Error(kUnknownError, "Current view doesnt support this command.");}    
#define NOT_IMPLEMENTED_IMPL    {*error = new Error(kUnknownError, "Command not implemented.");}
#define RET_IF_ERROR(e)         {if(e) {*error = e; return;}}

/// base class for QT based view's implementation
class QViewCmdExecutor : public ViewCmdExecutor {
public:
    explicit QViewCmdExecutor(Session* session, ViewId viewId);
    ~QViewCmdExecutor();

    virtual void CanHandleUrl(const std::string& url, bool* can, Error **error) = 0;
    virtual void GetTitle(std::string* title, Error **error);
    virtual void GetBounds(Rect *bounds, Error **error);
    virtual void SetBounds(const Rect& bounds, Error** error);
    virtual void Maximize(Error** error);
    virtual void GoForward(Error** error) = 0;
    virtual void GoBack(Error** error) = 0;
    virtual void Reload(Error** error) = 0;
    virtual void GetScreenShot(std::string* png, Error** error);
    virtual void GetSource(std::string* source, Error** error) = 0;
    virtual void SendKeys(const string16& keys, Error** error);
    virtual void SendKeys(const ElementId& element, const string16& keys, Error** error) = 0;
    virtual void MouseDoubleClick(Error** error) = 0;
    virtual void MouseButtonUp(Error** error) = 0;
    virtual void MouseButtonDown(Error** error) = 0;
    virtual void MouseClick(MouseButton button, Error** error) = 0;
    /// move mouse to position: cur_point + offset
    virtual void MouseMove(const int x_offset, const int y_offset, Error** error) = 0;
    /// Move the mouse by an offset of the specificed element
    virtual void MouseMove(const ElementId& element, int x_offset, const int y_offset, Error** error) = 0;
    /// the mouse will be moved to the center of the element
    virtual void MouseMove(const ElementId& element, Error** error) = 0;
    virtual void ClickElement(const ElementId& element, Error** error) = 0;
    virtual void GetAttribute(const ElementId& element, const std::string& key, base::Value** value, Error** error) = 0;
    virtual void ClearElement(const ElementId& element, Error** error) = 0;
    virtual void IsElementDisplayed(const ElementId& element, bool ignore_opacity, bool* is_displayed, Error** error) = 0;
    virtual void IsElementEnabled(const ElementId& element, bool* is_enabled, Error** error) = 0;
    virtual void ElementEquals(const ElementId& element1, const ElementId& element2, bool* is_equal, Error** error) = 0;
    virtual void GetElementLocation(const ElementId& element, Point* location, Error** error) = 0;
    virtual void GetElementLocationInView(const ElementId& element, Point* location, Error** error) = 0;
    virtual void GetElementTagName(const ElementId& element, std::string* tag_name, Error** error) = 0;
    virtual void IsOptionElementSelected(const ElementId& element, bool* is_selected, Error** error) = 0;
    virtual void SetOptionElementSelected(const ElementId& element, bool selected, Error** error) = 0;
    virtual void GetElementSize(const ElementId& element, Size* size, Error** error) = 0;
    virtual void ElementSubmit(const ElementId& element, Error** error) = 0;
    virtual void GetElementText(const ElementId& element, std::string* element_text, Error** error) = 0;
    virtual void GetElementCssProperty(const ElementId& element, const std::string& property, base::Value** value, Error** error) = 0;
    virtual void FindElement(const ElementId& root_element, const std::string& locator, const std::string& query, ElementId* element, Error** error) = 0;
    virtual void FindElements(const ElementId& root_element, const std::string& locator, const std::string& query, std::vector<ElementId>* elements, Error** error) = 0;
    virtual void ActiveElement(ElementId* element, Error** error) = 0;
    virtual void Close(Error** error);
    /// set view as current
    virtual void SwitchTo(Error** error);
    /// Switches the frame used by default. |name_or_id| is either the name or id
    /// of a frame element.
    virtual void SwitchToFrameWithNameOrId(const std::string& name_or_id, Error** error) = 0;
    /// Switches the frame used by default. |index| is the zero-based frame index.
    virtual void SwitchToFrameWithIndex(int index, Error** error) = 0;
    /// Switches to the frame identified by the given |element|. The element must
    /// be either an IFRAME or FRAME element.
    virtual void SwitchToFrameWithElement(const ElementId& element, Error** error) = 0;
    /// Switches the target frame to the topmost frame.
    virtual void SwitchToTopFrame(Error** error) = 0;
    virtual void NavigateToURL(const std::string& url, Error** error) = 0;
    virtual void GetURL(std::string* url, Error** error) = 0;
    virtual void ExecuteScript(const std::string& script, const base::ListValue* const args, base::Value** value, Error** error) = 0;
    virtual void ExecuteAsyncScript(const std::string& script, const base::ListValue* const args, base::Value** value, Error** error) = 0;
    virtual void GetAppCacheStatus(int* status, Error** error) = 0;
    virtual void GetAlertMessage(std::string* text, Error** error);
    virtual void SetAlertPromptText(const std::string& alert_prompt_text, Error** error);
    virtual void AcceptOrDismissAlert(bool accept, Error** error);

protected:
    Error* checkView(const ViewId& viewId, QWidget** widget);
    Rect ConvertQRectToRect(const QRect &rect);
    QRect ConvertRectToQRect(const Rect &rect);
private:
    DISALLOW_COPY_AND_ASSIGN(QViewCmdExecutor);
};

}  // namespace webdriver

#endif  // WEBDRIVER_Q_VIEW_EXECUTOR_H