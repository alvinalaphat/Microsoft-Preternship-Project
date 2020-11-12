#ifndef CATALOGUE_H
#define CATALOGUE_H

/* ---------------------------------------------------------------------- */

#include "Event.h"
#include "Interval.h"
#include "json.h"
#include "Fuzzy.h"
#include "Comparable.h"
#include <string>
#include <unordered_map>

/* ---------------------------------------------------------------------- */

class Entry
{

public:

  Entry();
  Entry(int p_id, std::string p_name, Event p_event);

  inline int id() const { return m_id; }
  inline std::string name() const { return m_name; }
  inline Event event() const { return m_event; }

  friend std::ostream& operator<<(std::ostream&, const Entry&);

private:

  int m_id;
  std::string m_name;
  Event m_event;

};

/* ---------------------------------------------------------------------- */

class Catalogue
{

  /**
   *  @brief Caches a name with id so that it can be searched for later.
   *  @param id The id associated with the name.
   *  @param name The name to cache.
   */
  void cache(int id, const std::string& name);

  /**
   * 
   * 
   * 
   */
  double tfidf(
    const std::unordered_map<std::string, size_t>& indiv,
    const std::unordered_map<std::string, size_t>& other
  );

  /**
   * 
   * 
   * 
   */
  void add_entry(Entry ent);

public:

  Catalogue();

  /**
   *  @brief Creates a catalogue from a given json filename.
   */
  Catalogue(std::string json_filename);

  /**
   *  @brief Loads a json file into this catalogue.
   *  @param json_filename The name of the json file to load.
   *  @return EXIT_SUCCESS on success, EXIT_FAILURE on failure. Note, on failure,
   *          this catalogue is not modified. On success, this catalogue is modified.
   */
  int load(std::string json_filename);

  /**
   *  @brief Returns the number of entries in this catalogue.
   *  @return The number of entries in this catalogue.
   */
  inline size_t size() const { return m_entries.size(); }

  /**
   *  @brief Returns the ids of the entries in this catalogue.
   *  @return A vector containing the ids of the entries in this catalogue.
   */
  std::vector<int> ids() const;

  // Both attempt to get Entry with given id, return empty Entry on failure.
  Entry get(int p_id);
  inline Entry operator[](int p_id) { return get(p_id); };

  // Returns TRUE if id exists in entries, else FALSE.
  inline bool has(int p_id) const { return m_entries.find(p_id) != m_entries.end(); }
  
  friend std::ostream& operator<<(std::ostream&, const Catalogue&);

  // Returns a vector of entries that are similar to name of class.
  std::vector<Comparable<Entry>> search(
    const std::string& name,
    size_t max_results,
    double threshold = 1.0);

private:

  std::unordered_map<int, Entry> m_entries;
  std::unordered_map<int, std::unordered_map<std::string, size_t>> m_indiv_cache;
  std::unordered_map<std::string, size_t> m_compos_cache;

};

/* ---------------------------------------------------------------------- */

#endif /* CATALOGUE_H */
