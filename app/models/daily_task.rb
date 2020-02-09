# frozen_string_literal: true

class DailyTask < ApplicationRecord
  belongs_to :user
  belongs_to :task
end
