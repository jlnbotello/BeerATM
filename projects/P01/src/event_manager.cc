#include "ev_manager.hh"

EventHandler::EventHandler()
{
  /*
  for (size_t i = 0; i < __EV_TABLE_LENGTH; i++)
  {
      handler_table[i] = nullptr;
  }  
  */
};

EventHandler::~EventHandler()
{
  while (m_callbacks) {
    auto temp = m_callbacks;
    m_callbacks = m_callbacks->next;
    delete temp;
  }
}

#if STL_AVAILABLE
bool EventHandler::add(Id_t id, std::function<void(void)> handler)
{
  if (id >= __EV_TABLE_LENGTH || !handler)
    return false;

  handler_table[id] = handler;

  return true;
};

bool EventHandler::trigger(Id_t id)
{
  if (id >= __EV_TABLE_LENGTH)
    return false;

  if (!handler_table[id])
    return false;

  handler_table[id]();

  return true;
};

EventRouter::EventRouter(){};

bool EventRouter::add(std::string url, EventHandler * evm)
{
  map.insert(std::pair<std::string, EventHandler *>(url,evm));
  return true;
};

bool EventRouter::route(std::string url, EventHandler::Id_t ev)
{
  std::map<std::string, EventHandler *>::iterator it;

  it = map.find(url);
  if (it != map.end())
  {
    it->second->trigger(ev);
    return true;
  }

  return false;
};

#else

bool EventHandler::trigger(Id_t id)
{
  for (callback_data_t<void>* data = m_callbacks; data; data = data->next) {
      if (data->id == id) {
          data->callback(data->obj);
          return true;
      }
  }
  return false;
};

EventRouter::EventRouter(){};

bool EventRouter::add(String url, EventHandler * evm)
{
  return map.insert(url, evm);
};

bool EventRouter::route(String url, EventHandler::Id_t ev)
{
  EventHandler * evm = map.find(url);
  if (evm)
  {
    evm->trigger(ev);
    return true;
  }
  return false;
};

#endif
